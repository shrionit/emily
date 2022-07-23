#include "UUID.h"
const std::string uuid::v4(){
    	UUID uuid;
		UuidCreate(&uuid);
		char *str;
		UuidToStringA(&uuid, (RPC_CSTR*)&str);
		const std::string uid = std::string(str);
		RpcStringFreeA((RPC_CSTR*)&str);
		return uid;
}
