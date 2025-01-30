#include "deribit.hpp"

int main(int argc, const char* argv[])
{
    DeribitConf conf;
    conf.remoteAddress = "test.deribit.com";
    conf.port = 9881;
    conf.apiKey = "WObvEb02";
    conf.secretKey = "trR2gzoedMBDhzQVv4WTFUuh2DxB7swQ2IstyTSKCBY";
    conf.senderCompId = "FIXCLIENT";
    conf.targetCompId = "DERIBITSERVER";

    DeribitMarketDataAdapter mda(conf);
    if (!mda.connectAndLogOn()) {
        mda.teardown();
        throw std::runtime_error("Failed to login");
    }
    mda.subscribeMarketData("BTC-PERPETUAL");

    try {
        while (true) {
            mda.perform();
        }
    } catch (const connection_exception& exc) {
        std::cout << "Exception: " << exc.what() << std::endl;
    }
    return 0;
}

