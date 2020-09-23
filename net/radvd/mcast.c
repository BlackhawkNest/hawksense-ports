#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>

int main()
{
	struct ipv6_mreq mreq;                                                  
	int sock;

	sock = socket(AF_INET6, SOCK_RAW, IPPROTO_ICMPV6);
	if (sock < 0) {
       printf("socket fail\n");
		return (-1);
	}
                                                                               
       memset(&mreq, 0, sizeof(mreq));                                         
      mreq.ipv6mr_interface = 10;
                                                                           
      /* all-routers multicast address */                                     
        if (inet_pton(AF_INET6, "ff02::2",                                      
                       &mreq.ipv6mr_multiaddr.s6_addr) != 1) {                 
       printf("address fail\n");
               return (-1);                                                    
       }                                                                       
                                        
					while (1) {
      /* if we leave unconditionally the join cannot fail */                  
       if (setsockopt(sock, IPPROTO_IPV6, IPV6_LEAVE_GROUP, &mreq, sizeof(mreq)) < 0) {
       printf("oh uh\n");
       }
                                                                               
     if (setsockopt(sock, IPPROTO_IPV6, IPV6_JOIN_GROUP,                     
                        &mreq, sizeof(mreq)) < 0) {                             
       printf("join fail\n");
               //return (-1);                                                    
       }                                                                       
       }
                                                                                
       return 0;       
}
