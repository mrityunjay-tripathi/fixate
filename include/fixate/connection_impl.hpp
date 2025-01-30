/**
* @file fixate/connection_impl.hpp
* @author Mrityunjay Tripathi
*
* Connection is a base class implementation for various network/file stream
* sources, through which FIX messages can exchanged.
*
* fixate is free software; you may redistribute it and/or modify it under the
* terms of the BSD 2-Clause "Simplified" License. You should have received a copy of the
* BSD 2-Clause "Simplified" License along with fixate. If not, see
* http://www.opensource.org/licenses/BSD-2-Clause for more information.
*
* Copyright (c) 2025, Mrityunjay Tripathi
*/

#ifndef FIXATE_CONNECTION_IMPL_HPP_
#define FIXATE_CONNECTION_IMPL_HPP_

#include "fixate/connection.hpp"
#include "fixate/fixdatetime.hpp"

namespace fixate
{
    template <typename ConnectionType>
    base_connection<ConnectionType>::base_connection(const std::string& remote_address, int port,
                on_connect on_connect_cb, on_disconnect on_disconnect_cb, on_error on_error_cb)
        : port(port), remote_address(remote_address), vrb_context(nullptr),
                on_connect_cb(on_connect_cb), on_disconnect_cb(on_disconnect_cb), on_error_cb(on_error_cb)
    {
        size_t capacity = 1 << 20; // 1 MB of data can be buffered.
        std::string name = std::string("shmqueue-") + char('0' + char(rand() % 10));
        vrb_context = vrb_ctx_create(capacity, name.c_str());
    }

    template <typename ConnectionType>
    base_connection<ConnectionType>::base_connection(base_connection&& other)
        : is_active(false) { *this = std::move(other); }

    template <typename ConnectionType>
    base_connection<ConnectionType>& base_connection<ConnectionType>::operator=(base_connection&& other) {
        if (this != &other) {
            if (this->active()) { disconnect(); }
            sockfd = std::move(other.sockfd);
            is_active = std::move(other.is_active);
            port = std::move(other.port);
            remote_address = std::move(other.remote_address);
            last_read_timestamp = std::move(other.last_read_timestamp);
            last_sent_timestamp = std::move(other.last_sent_timestamp);
            on_connect_cb = std::move(other.on_connect_cb);
            on_error_cb = std::move(other.on_error_cb);
            vrb_context = other.vrb_context;
            other.vrb_context = nullptr;
        }
        return *this;
    }

    template <typename ConnectionType>
    base_connection<ConnectionType>::~base_connection() { vrb_ctx_destroy(vrb_context); }

    template <typename ConnectionType>
    int64_t base_connection<ConnectionType>::system_timestamp() {
        timespec ts;
        ::clock_gettime(CLOCK_REALTIME, &ts);
        return (int64_t)ts.tv_sec * 1e+9 + ts.tv_nsec;
    }

    template <typename ConnectionType>
    int base_connection<ConnectionType>::close_file_descriptor(int fd) {
        int ec = close(fd);
        if (ec != 0) throw connection_exception(ec, "Failed to close file descriptor.");
        return ec;
    }
    template <typename ConnectionType>
    int base_connection<ConnectionType>::connect() {
        return static_cast<ConnectionType*>(this)->connect();
    }

    template <typename ConnectionType>
    int base_connection<ConnectionType>::disconnect() {
        return static_cast<ConnectionType*>(this)->disconnect();
    }

    template <typename ConnectionType>
    const char* base_connection<ConnectionType>::read_ptr() {
        return reinterpret_cast<const char*>(vrb_prefetch_head(vrb_context));
    }

    template <typename ConnectionType>
    int base_connection<ConnectionType>::move_head(int size) {
        return vrb_move_head(vrb_context, size);
    }

    template <typename ConnectionType>
    int base_connection<ConnectionType>::size() {
        return vrb_size(vrb_context);
    }

    template <typename ConnectionType>
    int base_connection<ConnectionType>::poll() {
        return static_cast<ConnectionType*>(this)->poll();
    }

    template <typename ConnectionType>
    int base_connection<ConnectionType>::send_message(const char *buffer, int size) {
        return static_cast<ConnectionType*>(this)->send_message(buffer, size);
    }

    template <typename ConnectionType>
    bool base_connection<ConnectionType>::active() const { return is_active; }

    template <typename ConnectionType>
    int64_t base_connection<ConnectionType>::last_sent_at() const { return last_sent_timestamp; }

    template <typename ConnectionType>
    int64_t base_connection<ConnectionType>::last_read_at() const { return last_read_timestamp; }

    template <typename ConnectionType>
    bool base_connection<ConnectionType>::has_data() {
        // check if there is data to read
        fd_set readfd;
        FD_ZERO(&readfd);
        FD_SET(sockfd, &readfd);

        struct timeval tv;
        tv.tv_sec = 0;
        tv.tv_usec = 5; // Set timeout to be 5 microseconds.
        int ret = select(sockfd + 1, &readfd, NULL, NULL, &tv);
        if (ret < 0) { on_error_cb(errno, strerror(errno)); }
        return FD_ISSET(sockfd, &readfd);
    }
}

namespace fixate
{
    tcp_client::tcp_client(const std::string& remote_address, int port,
                on_connect on_connect_cb, on_disconnect on_disconnect_cb, on_error on_error_cb)
        : base(remote_address, port, on_connect_cb, on_disconnect_cb, on_error_cb) {}

    tcp_client::tcp_client(tcp_client&& other)
        : base(static_cast<base&&>(other)) {}

    tcp_client& tcp_client::operator=(tcp_client&& other) {
        if (this != &other) {
            base::operator=(std::move(static_cast<base&&>(other)));
        }
        return *this;
    }

    tcp_client::~tcp_client() { disconnect(); }

    void tcp_client::error_handler() {
        int ec = errno;
        switch (ec) {
            case EAGAIN: break;
            default: on_error_cb(ec, strerror(ec)); break;
        }
    }

    int tcp_client::connect()
    {
        std::string port_str = std::to_string(this->port);
        this->sockfd = open_connection(this->remote_address.c_str(), port_str.c_str());
        if (this->sockfd != -1) {
            this->is_active = true;
            on_connect_cb();
        }
        return this->sockfd;
    }

    int tcp_client::disconnect()
    {
        if (!this->is_active) return !this->is_active;
        on_disconnect_cb();
        int ec = close_file_descriptor(this->sockfd);
        this->is_active = false;
        return ec;
    }

    int tcp_client::poll()
    {
        void* buffer = reinterpret_cast<void*>(vrb_prefetch_tail(vrb_context));
        int size = this->MAX_READ_SIZE;
        int bytes_read = recv(this->sockfd, buffer, size, 0);
        if (bytes_read > 0) {
            vrb_move_tail(vrb_context, bytes_read);
            last_read_timestamp = system_timestamp();
        }
        else { error_handler(); }
        return bytes_read;
    }

    int tcp_client::send_message(const char *buffer, int size)
    {
        int64_t now = system_timestamp();
        int bytes_written = 0;
        while (bytes_written < size) {
            const void* ptr = (const void*)(buffer + bytes_written);
            int bytes_sent = send(this->sockfd, ptr, size - bytes_written, 0);
            if (bytes_sent > 0) { bytes_written += bytes_sent; }
            else if (bytes_sent < 0) { error_handler(); }
            else { disconnect(); }
        }
        last_sent_timestamp = now;
        return bytes_written;
    }

    int tcp_client::open_connection(const char *hostname, const char *port)
    {
        struct addrinfo hints;
        std::memset(&hints, 0, sizeof(struct addrinfo));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;

        struct addrinfo *addrs = nullptr;
        int status = getaddrinfo(hostname, port, &hints, &addrs);
        if (status != 0) {
            on_error_cb(errno, strerror(errno));
            throw connection_exception(errno, std::string(hostname) + ": " + gai_strerror(status));
        }
        int sfd = -1, err = 0;
        for (struct addrinfo *addr = addrs; addr != nullptr; addr = addr->ai_next) {
            sfd = socket(addrs->ai_family, addrs->ai_socktype, addrs->ai_protocol);
            if (sfd == this->DEFAULT_ERROR_CODE) { err = errno; continue; }
            // Set non-blocking socket.
            int flags = fcntl(sfd, F_GETFL, 0);
            fcntl(sfd, F_SETFL, flags | O_NONBLOCK);
            int connect_ec = ::connect(sfd, addr->ai_addr, addr->ai_addrlen);
            if (connect_ec == 0) break;
            err = errno;
            if (err != EINPROGRESS) {
                on_error_cb(err, strerror(err));
                close_file_descriptor(sfd);
                sfd = this->DEFAULT_ERROR_CODE;
            }
            else break;
        }
        freeaddrinfo(addrs);
        if (sfd == this->DEFAULT_ERROR_CODE) { on_error_cb(err, strerror(err)); }
        return sfd;
    }

}


namespace fixate {

    namespace details {

        static int FIXATE_SSL_CTX_COUNT = 0;
        static SSL_CTX* FIXATE_SSL_CTX_RAW = nullptr;
        static SSL_CTX* ssl_ctx_create()
        {
            if (FIXATE_SSL_CTX_RAW == nullptr)
            {
#if OPENSSL_VERSION_NUMBER < 0x10100000L
                SSL_library_init();
                SSL_load_error_strings();
                const SSL_METHOD *method = TLSv1_2_client_method();
#else
                OPENSSL_init_ssl(OPENSSL_INIT_LOAD_SSL_STRINGS, NULL);
                const SSL_METHOD *method = TLS_client_method();
#endif
                FIXATE_SSL_CTX_RAW = SSL_CTX_new(method);
            }
            FIXATE_SSL_CTX_COUNT++;
            return FIXATE_SSL_CTX_RAW;
        }
        static void ssl_ctx_destroy() {
            if (FIXATE_SSL_CTX_COUNT-- == 0)
                SSL_CTX_free(FIXATE_SSL_CTX_RAW);
        }
    }

    tcp_ssl_client::tcp_ssl_client(const std::string& remote_address, int port,
                on_connect on_connect_cb, on_disconnect on_disconnect_cb, on_error on_error_cb)
        : base(remote_address, port, on_connect_cb, on_disconnect_cb, on_error_cb)
    {
        ssl_context = details::ssl_ctx_create();
    }

    tcp_ssl_client::tcp_ssl_client(tcp_ssl_client&& other)
        : base(static_cast<base&&>(other))
    {
        ssl = std::move(other.ssl); other.ssl = nullptr;
        ssl_context = std::move(other.ssl_context); other.ssl_context = nullptr;
    }

    tcp_ssl_client& tcp_ssl_client::operator=(tcp_ssl_client&& other) {
        if (this != &other) {
            base::operator=(std::move(static_cast<base&&>(other)));
            ssl = std::move(other.ssl); other.ssl = nullptr;
            ssl_context = std::move(other.ssl_context); other.ssl_context = nullptr;
        }
        return *this;
    }

    tcp_ssl_client::~tcp_ssl_client() {
        disconnect();
        if (ssl) SSL_free(ssl);
        details::ssl_ctx_destroy();
    }

    void tcp_ssl_client::error_handler(int ret_val) {
        int ec = SSL_get_error(ssl, ret_val);
        switch (ec)
        {
            case SSL_ERROR_WANT_WRITE: break;
            case SSL_ERROR_WANT_READ: break;
            case SSL_ERROR_ZERO_RETURN: disconnect(); break;
            default:
                this->is_active = false;
                on_error_cb(errno, strerror(errno));
                break;
        }
    }

    int tcp_ssl_client::connect()
    {
        std::string port_str = std::to_string(this->port);
        this->sockfd = open_connection(this->remote_address.c_str(), port_str.c_str());
        if (this->sockfd != -1) {
            this->is_active = true;
            on_connect_cb();
        }
        return this->sockfd;
    }

    int tcp_ssl_client::disconnect()
    {
        if (!this->is_active) return !this->is_active;
        on_disconnect_cb();
        SSL_shutdown(ssl);
        int ec = close_file_descriptor(this->sockfd);
        this->is_active = false;
        return ec;
    }

    int tcp_ssl_client::poll()
    {
        if (!this->is_active)
            return 0;

        void* buffer = reinterpret_cast<void*>(vrb_prefetch_tail(vrb_context));
        int size = this->MAX_READ_SIZE;
        int bytes_read = SSL_read(ssl, buffer, size);
        if (bytes_read > 0) {
            vrb_move_tail(vrb_context, bytes_read);
            last_read_timestamp = system_timestamp();
        }
        else if (bytes_read < 0) { error_handler(bytes_read); }
        else { disconnect(); }
        return bytes_read;
    }

    int tcp_ssl_client::send_message(const char *buffer, int size)
    {
        int64_t now = system_timestamp();
        int bytes_written = 0;
        while (bytes_written < size) {
            const void* ptr = (const void*)(buffer + bytes_written);
            int bytes_sent = SSL_write(ssl, ptr, size - bytes_written);
            if (bytes_sent > 0)  { bytes_written += bytes_sent; }
            else if (bytes_sent < 0) { error_handler(bytes_sent); }
            else { disconnect(); }
        }
        last_sent_timestamp = now;
        return bytes_written;
    }

    int tcp_ssl_client::open_connection(const char *hostname, const char *port)
    {
        struct addrinfo hints;
        std::memset(&hints, 0, sizeof(struct addrinfo));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;

        struct addrinfo *addrs = nullptr;
        int status = getaddrinfo(hostname, port, &hints, &addrs);
        if (status != 0) {
            on_error_cb(errno, strerror(errno));
            throw connection_exception(errno, std::string(hostname) + ": " + gai_strerror(status));
        }
        int sfd = -1, err = 0;
        for (struct addrinfo *addr = addrs; addr != nullptr; addr = addr->ai_next) {
            sfd = socket(addrs->ai_family, addrs->ai_socktype, addrs->ai_protocol);
            if (sfd == this->DEFAULT_ERROR_CODE) { err = errno; continue; }
            // Set non-blocking socket.
            int flags = fcntl(sfd, F_GETFL, 0);
            fcntl(sfd, F_SETFL, flags | O_NONBLOCK);
            int connect_ec = ::connect(sfd, addr->ai_addr, addr->ai_addrlen);
            if (connect_ec == 0) break;
            err = errno;
            if (err != EINPROGRESS) {
                on_error_cb(err, strerror(err));
                close_file_descriptor(sfd);
                sfd = this->DEFAULT_ERROR_CODE;
            }
            else break;
        }
        freeaddrinfo(addrs);
        if (sfd == this->DEFAULT_ERROR_CODE) { on_error_cb(err, strerror(err)); }
        else {
            ssl = SSL_new(ssl_context);
            if (ssl == NULL) { disconnect(); return -1; }
            // Set non-blocking socket.
            int flags = fcntl(sfd, F_GETFL, 0);
            fcntl(sfd, F_SETFL, flags | O_NONBLOCK);

            SSL_set_fd(ssl, sfd);
            fd_set fds;
            FD_ZERO(&fds);
            FD_SET(sfd, &fds);

            bool connected = false;
            int tries = 25;
            while (!connected && tries--) {
                int ret = SSL_connect(ssl);
                if (ret == 1) { connected = true; break; }
                int ec = SSL_get_error(ssl, ret);
                switch (ec) {
                    case SSL_ERROR_WANT_READ:
                    {
                        int err_r = select(sfd + 1, &fds, NULL, NULL, NULL);
                        if (err_r == -1) { disconnect(); return -1; }
                    }
                    break;
                    case SSL_ERROR_WANT_WRITE:
                    {
                        int err_w = select(sfd + 1, NULL, &fds, NULL, NULL);
                        if (err_w == -1) { disconnect(); return -1; }
                    }
                    break;
                    default: disconnect(); return -1;
                }
            }
            if (!connected && tries == 0) {
                throw connection_exception(0, "Connection timed out."
                        " hostname: \"" + std::string(hostname) +
                        "\", port: \"" + std::string(port) + "\"");
            }
        }
        return sfd;
    }

}

namespace fixate {

    udp_client::udp_client(const std::string& remote_address, int port,
                on_connect on_connect_cb, on_disconnect on_disconnect_cb, on_error on_error_cb)
        : base(remote_address, port, on_connect_cb, on_disconnect_cb, on_error_cb) {}

    udp_client::udp_client(udp_client&& other)
        : base(static_cast<base&&>(other))
    {
        server_addr = std::move(other.server_addr);
    }

    udp_client& udp_client::operator=(udp_client&& other) {
        if (this != &other) {
            base::operator=(std::move(static_cast<base&&>(other)));
            server_addr = std::move(other.server_addr);
        }
        return *this;
    }

    udp_client::~udp_client() { disconnect(); }

    void udp_client::error_handler() {
        int ec = errno;
        switch (ec) {
            case EAGAIN: break;
            default: on_error_cb(ec, strerror(ec)); break;
        }
    }

    int udp_client::connect()
    {
        std::string port_str = std::to_string(this->port);
        this->sockfd = open_connection(this->remote_address.c_str(), port_str.c_str());
        if (this->sockfd != -1) {
            this->is_active = true;
            on_connect_cb();
        }
        return this->sockfd;
    }

    int udp_client::disconnect()
    {
        if (!this->is_active) return !this->is_active;
        on_disconnect_cb();
        int ec = close_file_descriptor(this->sockfd);
        this->is_active = false;
        return ec;
    }

    int udp_client::poll()
    {
        void* buffer = reinterpret_cast<void*>(vrb_prefetch_tail(vrb_context));
        int size = this->MAX_READ_SIZE;
        struct sockaddr_in sender_addr;
        socklen_t addr_size = sizeof(server_addr);
        int bytes_read = recvfrom(this->sockfd, buffer, size, 0, (struct sockaddr*)&sender_addr, &addr_size);
        if (bytes_read > 0) {
            vrb_move_tail(vrb_context, bytes_read);
            last_read_timestamp = system_timestamp();
        }
        else if (bytes_read < 0) { error_handler(); }
        else { disconnect(); }
        return bytes_read;
    }

    int udp_client::send_message(const char *buffer, int size)
    {
        int64_t now = system_timestamp();
        int bytes_written = 0;
        while (bytes_written < size) {
            const void* ptr = (const void*)(buffer + bytes_written);
            int bytes_sent = sendto(this->sockfd, ptr, size - bytes_written, 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
            if (bytes_sent > 0) { bytes_written += bytes_sent; }
            else if (bytes_sent < 0) { error_handler(); }
            else { disconnect(); }
        }
        last_sent_timestamp = now;
        return bytes_written;
    }

    int udp_client::open_connection(const char *hostname, const char *port)
    {
        struct addrinfo hints;
        std::memset(&hints, 0, sizeof(struct addrinfo));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_DGRAM;
        hints.ai_protocol = IPPROTO_UDP;

        struct addrinfo *addrs = nullptr;
        int status = getaddrinfo(hostname, port, &hints, &addrs);
        if (status != 0) {
            on_error_cb(errno, strerror(errno));
            throw connection_exception(errno, std::string(hostname) + ": " + gai_strerror(status));
        }
        int sfd = -1, err = 0;
        for (struct addrinfo *addr = addrs; addr != nullptr; addr = addr->ai_next) {
            sfd = socket(addrs->ai_family, addrs->ai_socktype, addrs->ai_protocol);
            if (sfd == this->DEFAULT_ERROR_CODE) { err = errno; continue; }
            // Set non-blocking socket.
            int flags = fcntl(sfd, F_GETFL, 0);
            fcntl(sfd, F_SETFL, flags | O_NONBLOCK);

            server_addr = *(struct sockaddr_in*)addr->ai_addr;
            break;
        }
        freeaddrinfo(addrs);
        if (sfd == this->DEFAULT_ERROR_CODE) { on_error_cb(err, strerror(err)); }
        return sfd;
    }

}

namespace fixate {

    file_client::file_client(const std::string& filename,
                on_connect on_connect_cb = nullptr, on_disconnect on_disconnect_cb = nullptr, on_error on_error_cb = nullptr)
        : base("", 0, on_connect_cb, on_disconnect_cb, on_error_cb), filename(filename) {}

    file_client::file_client(file_client&& other)
        : base(static_cast<base&&>(other))
    {
        filename = std::move(other.filename);
        rfile = std::move(other.rfile); other.rfile = nullptr;
        wfile = std::move(other.wfile); other.wfile = nullptr;
    }

    file_client& file_client::operator=(file_client&& other) {
        if (this != &other) {
            base::operator=(std::move(static_cast<base&&>(other)));
            filename = std::move(other.filename);
            rfile = std::move(other.rfile); other.rfile = nullptr;
            wfile = std::move(other.wfile); other.wfile = nullptr;
        }
        return *this;
    }
    file_client::~file_client() { disconnect(); }

    void file_client::error_handler(io_error ec, const std::string& msg) {
        throw connection_exception(static_cast<int>(ec), msg);
    }

    FILE* file_client::fopen_or_die(const char *filename, const char *instruction)
    {
        FILE *const f = fopen(filename, instruction);
        if (f == nullptr)
            error_handler(io_error::fopen, "Failed to open file: \"" + std::string(filename) + "\"");
        return f;
    }

    void file_client::fclose_or_die(FILE *file)
    {
        if (fclose(file))
            error_handler(io_error::fclose, "Failed to close file: \"" + std::string(filename) + "\"");
    }

    size_t file_client::fsize_or_die(const char *filename)
    {
        struct stat st;
        if (stat(filename, &st) != 0)
            error_handler(io_error::fsize, "Failed to stat file: \"" + std::string(filename) + "\"");

        off_t const file_size = st.st_size;
        size_t const size = (size_t)file_size;
        if ((file_size < 0) || (file_size != (off_t)size))
            error_handler(io_error::fsize, "File size too large: \"" + std::string(filename) + "\"");

        return size;
    }

    int file_client::connect()
    {
        std::string wfilename = filename + "_output";
        rfile = fopen_or_die(filename.c_str(), "rb");
        wfile = fopen_or_die(wfilename.c_str(), "wb");
        if (fsize_or_die(filename.c_str()) <= 0)
            error_handler(io_error::fsize, "File \"" + filename + "\" is empty.");
        this->is_active = true;
        on_connect_cb();
        return 1;
    }

    int file_client::disconnect()
    {
        if (!this->is_active) return !this->is_active;
        on_disconnect_cb();
        fclose_or_die(rfile);
        fclose_or_die(wfile);
        this->is_active = false;
        return 1;
    }

    int file_client::poll()
    {
        if (!this->is_active) return 0;

        void* buffer = reinterpret_cast<void*>(vrb_prefetch_tail(vrb_context));
        int size = this->MAX_READ_SIZE;
        int bytes_read = fread(buffer, 1, size, rfile);
        if (bytes_read > 0) {
            vrb_move_tail(vrb_context, bytes_read);
            last_read_timestamp = system_timestamp();
        }
        else if (feof(rfile)) {
            last_read_timestamp = system_timestamp();
            disconnect();
            error_handler(io_error::fread, "stream ended.");
        }
        else { error_handler(io_error::fread, "fread"); }
        return bytes_read;
    }

    int file_client::send_message(const char *buffer, int size)
    {
        int64_t now = system_timestamp();
        int bytes_written = 0;
        while (bytes_written < size) {
            const void* ptr = (const void*)(buffer + bytes_written);
            int bytes_sent = fwrite(ptr, 1, size - bytes_written, wfile);
            if (bytes_sent == size) { bytes_written += bytes_sent; }
            else { error_handler(io_error::fwrite, "fwrite"); }
        }
        last_sent_timestamp = now;
        return bytes_written;
    }

}
#endif

