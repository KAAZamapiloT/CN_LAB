# include < stdio .h >
 # include < stdlib .h >
 # include < string .h >
 # include < unistd .h >
 # include < arpa / inet .h >

 # define PORT 12345

 int main () {
 int sock = 0;
 struct sockaddr_in serv_addr ;
 char buffer [1024] = {0};
 char * hello = " Hello ␣Server ,␣ this ␣is␣ Client .";

sock = socket ( AF_INET , SOCK_STREAM , 0) ;
 if ( sock < 0) {
 perror (" Socket ␣ creation ␣ error ") ;
 return -1;
 }

serv_addr . sin_family = AF_INET ;
 serv_addr . sin_port = htons ( PORT ) ;

if ( inet_pton ( AF_INET , " 192.168.1.1 ", & serv_addr . sin_addr ) <= 0) { printf (" Invalid ␣ address /␣ Address ␣not ␣ supported \n") ;
 return -1;
 }

 if ( connect ( sock , ( struct sockaddr *) & serv_addr , sizeof ( serv_addr ) )

< 0) {

 perror (" Connection ␣ Failed ") ;
return -1;
 }
 send ( sock , hello , strlen ( hello ) , 0) ;
 printf (" Message ␣ sent ␣to␣ server .\n") ;

 read ( sock , buffer , 1024) ;
 printf (" Server ␣ says :␣%s\n", buffer ) ;

 close ( sock ) ;
 return 0;
}