#include "ros/ros.h"
#include "ros/time.h"
#include "GATE_ZigBee/ZigbeeFrame.h"
#include "zigbee_ros/zigbeeStorer.h"

#include <signal.h>

#include <sstream>
#include <vector>
#include <algorithm>
#include <time.h>



/*################### ZIGBEESOTRER*/

/*
 * Init function:
 *  - open serial port
 *  - init structures
 */
int init(void) {
   serialPort = serialPort0;

   /*
    * Try to open serial port
    */
   if ((sd = open(serialPort, O_RDWR | O_NOCTTY | O_NDELAY)) == -1)
   {
      fprintf(stderr, "Unable to open the serial port %s - \n", serialPort);
      exit(-1);
   }
   else
   {
      if (!sd)
      {
         sd = open(serialPort, O_RDWR | O_NOCTTY | O_NDELAY);
      }
      fcntl(sd, F_SETFL, 0);
   }

   tcgetattr(sd, &opciones);
   cfsetispeed(&opciones, B38400);
   cfsetospeed(&opciones, B38400);
   opciones.c_cflag |= (CLOCAL | CREAD);

   /*
    * No parity
    */
   opciones.c_cflag &= ~PARENB;
   opciones.c_cflag &= ~CSTOPB;
   opciones.c_cflag &= ~CSIZE;
   opciones.c_cflag |= CS8;

   /*
    * raw input:
    * making the application ready to receive
    */
   opciones.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

   /*
    * Ignore parity errors
    */
   opciones.c_iflag |= ~(INPCK | ISTRIP | PARMRK);
   opciones.c_iflag |= IGNPAR;
   opciones.c_iflag &= ~(IXON | IXOFF | IXANY | IGNCR | IGNBRK);
   opciones.c_iflag |= BRKINT;

   /*
    * raw output
    * making the applycation ready to transmit
    */
   opciones.c_oflag &= ~OPOST;

   /*
    * apply
    */
   tcsetattr(sd, TCSANOW, &opciones);

   return 0;
}

/*
 * getFrame function:
 *  - read bytes from serial port
 *  - build a string containing the data of the received message
 *  - the data frame is limited by two symbols : '&' for the begin and '@' for the end
 * This function uses the @ symbol to stop reading the serial buffer
 */
void getFrame() {
	//fprintf(stderr,"Zigbee PRO log started .... (MPIGate)\n");

   char c;
   int j = 0;

   //Get frame char by char untill '\n'
   while (1)
   {
      read(sd,&c,1);

      if((c=='\0') || (c=='\r'))
      {
         //Carriage return chars are modified
         aux[j]='_';

      }
      else // Other characters are stored in aux[]
      {
         aux[j]=c;
	//fprintf(stderr,"%c",aux[j]);
         j++;

      }

      if((c=='\n') || (j==(MAX-1))) 
      {
         aux[j]='\0';
	//  fprintf(stderr,"\n");
         break;
      }
   }
	//fprintf(stderr,"FIN \n\n\n");
}



void parseFrame(struct xbee_frame *p_frame, struct xbee_dataframe *p_mydataframe) {
   
	char *_symbolStart, *_symbolEnd;
	int indexStart, indexFin, indexLimit,indexOfmyData, NumberOfData;

	

   char *aux2,*aux3;
   aux2 = strpbrk(aux, "&"); // look for the begining of the data frame
	aux3 = strpbrk(aux2, "@"); // look for the end of the data frame
	
	indexLimit = aux3-aux2;  //max length of the read string
	
/*
   //Get mac value

	_macStart=strchr(aux2,'#');
   index=_macStart-aux2;
	
   strncpy(p_frame->mac,aux2+index+1,16);
//	fprintf(stderr,"mac1=%s",p_frame->mac);
	fprintf(stderr,"_macStart=[%s], index=%d, ",_macStart, index);
	
   p_frame->mac[16] = '\0';
	fprintf(stderr,"[p_frame->mac=%s] \n",p_frame->mac);

   index = index+2+16+4;
*/

//init counters	
	indexStart = 0; 	
	NumberOfData=0;
	indexOfmyData=0;
	//int j=0;
	// the indexStart is 0 as the field data after the '&' is the ID, it is incremented at the end of the while to read the next field
	
	while (indexStart<indexLimit-1) { //while the pointer of field reading less than the limit

//		fprintf(stderr,"indexStart=%d,indexLimit=%d\n",indexStart,indexLimit);

		
//		fprintf(stderr,"NumberOfData=%d,indexOfmyData=%d\n",NumberOfData,indexOfmyData);
		
//		fprintf(stderr,"[indexStart =%d,",indexStart);
		_symbolEnd = strchr(aux2+(indexStart+1),'#');				//identification of the end  of field 
		indexFin = _symbolEnd - aux2;										//distance from the begining of the identified string
		//		fprintf(stderr,"indexFin =%d]",indexFin);
		
		if (NumberOfData==0) {												//First field is ID
				strncpy(p_mydataframe->iD,aux2+(indexStart+1),(indexFin-1)-indexStart);
				p_mydataframe->iD[(indexFin-1)-indexStart]='\0';
//				fprintf(stderr,"ID: (%s)\n",myIdentity.iD);

			}
		if (NumberOfData==1) {												//2nd field is location
				strncpy(p_mydataframe->location,aux2+(indexStart+1),(indexFin-1)-indexStart);
				p_mydataframe->location[(indexFin-1)-indexStart]='\0';
//				fprintf(stderr,"location: (%s)\n",myIdentity.location);

			}
		if(NumberOfData==2){													//3rd field is time (it coul be empty but it's always between two ##
				strncpy(p_mydataframe->time,aux2+(indexStart+1),(indexFin-1)-indexStart);
				p_mydataframe->time[(indexFin-1)-indexStart]='\0';
//				fprintf(stderr,"time: (%s)\n",myIdentity.time);

			}
		if (NumberOfData>2){													//After 3rd field the data arrives in couples (Name,Value)
			if (NumberOfData%2==0){											//Pair number after the time field is Value
				strncpy((p_mydataframe->sensor[indexOfmyData]).variableValue,aux2+(indexStart+1),(indexFin-1)-indexStart);
			   p_mydataframe->sensor[indexOfmyData].variableValue[(indexFin-1)-indexStart]='\0';
//				fprintf(stderr,"Value: (%s), %d\n",p_mydataframe->sensor[indexOfmyData].variableValue,NumberOfData);
				p_mydataframe->numberOfReadings=indexOfmyData; //number of stored readings
				indexOfmyData++; //increment for next couple (variableName,variableValue) reading
				

			}
			else {																//Odd number after the time field is Name
				strncpy((p_mydataframe->sensor[indexOfmyData]).variableName,aux2+(indexStart+1),(indexFin-1)-indexStart);
				p_mydataframe->sensor[indexOfmyData].variableName[(indexFin-1)-indexStart]='\0';
//				fprintf(stderr,"Name: (%s),\n",p_mydataframe->sensor[indexOfmyData].variableName);
			}
		}
	
		NumberOfData++;
//		fprintf(stderr,"indexLimit = %d\n", indexLimit);
		indexStart = indexFin;
		_symbolStart = strchr(aux2+indexStart,'#');					// start reading point
		indexStart =_symbolStart - aux2; 								//distance from the begining of the identified string

		
		
	}


}

/*################################*/

