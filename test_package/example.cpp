#include <quickfix/FileStore.h>
#include <quickfix/FileLog.h>
#include <quickfix/SocketAcceptor.h>
#include <quickfix/Session.h>
#include <quickfix/SessionSettings.h>
#include <quickfix/Application.h>

int main(int argc, char** argv) {
	try {
		if (argc < 2)
			return 0;


		std::string fileName = argv[1];

		FIX::SessionSettings settings(fileName);
		FIX::FileStoreFactory storeFactory(settings);
		FIX::FileLogFactory logFactory(settings);

		return 0;
	} catch (FIX::ConfigError& e) {
		std::cout << e.what();
		return 1;
	}
}
