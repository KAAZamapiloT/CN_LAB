// server .c
 # include < stdio .h >
 # include < stdlib .h >
 # include < string .h >
 # include < unistd .h >
 # include < arpa / inet .h >

 # define PORT 12345

 int main () {
 int server_fd , new_socket ;
 struct sockaddr_in address ;
int opt = 1;
 int addrlen = sizeof ( address ) ;
 char buffer [1024] = {0};
 char * hello = " Hello ␣Client ,␣ message ␣ received !";

 server_fd = socket ( AF_INET , SOCK_STREAM , 0) ;
 if ( server_fd == 0) {
 perror (" Socket ␣ failed ") ;
 exit ( EXIT_FAILURE ) ;
 }
 setsockopt ( server_fd , SOL_SOCKET , SO_REUSEADDR | SO_REUSEPORT , & opt

, sizeof ( opt ) ) ;

 address . sin_family = AF_INET ;
 address . sin_addr . s_addr = INADDR_ANY ;
 address . sin_port = htons ( PORT ) ;

 if ( bind ( server_fd , ( struct sockaddr *) & address , sizeof ( address ) ) <

0) {

 perror (" Bind ␣ failed ") ;
 exit ( EXIT_FAILURE ) ;
 }

 if ( listen ( server_fd , 3) < 0) {
perror (" Listen ␣ failed ") ;
 exit ( EXIT_FAILURE ) ;
 }
 printf (" Server ␣ listening ␣on␣ port ␣%d ...\ n", PORT ) ;

 new_socket = accept ( server_fd , ( struct sockaddr *) & address , (

socklen_t *) & addrlen ) ;
 if ( new_socket < 0) {
perror (" Accept ␣ failed ") ;
 exit ( EXIT_FAILURE ) ;
 }

 read ( new_socket , buffer , 1024) ;
 printf (" Client ␣ says :␣%s\n", buffer ) ;

 send ( new_socket , hello , strlen ( hello ) , 0) ;
 printf (" Response ␣ sent ␣to␣ client .\n") ;
 close ( new_socket ) ;
 close ( server_fd ) ;


 return 0;
 }