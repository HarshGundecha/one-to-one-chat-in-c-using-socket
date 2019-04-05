// #define GET_MACRO(_1,_2,_3,NAME,...) NAME
// #define FOO(...) GET_MACRO(__VA_ARGS__, FOO3, FOO2)(__VA_ARGS__)

int OpenSocketFDGeneric(char user, char *hostname, char *port);
int GetClientFD(int listenfd);