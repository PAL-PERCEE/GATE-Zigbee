#include "zigbee_ros/zigbeeStorer.cpp"

using namespace std;


/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */
std::string node_name = "MADYNESGate";

ros::Publisher chatter_pub[10] = {}; //Nombre MAX de TOPIC

std::vector<string> CAP_LIST; // L'annuaire des capteurs inscrit
vector<string>::iterator it;

ros::Timer timer2;

ros::Duration duration = one_min;

    typedef struct { 
        char *name; 
        ros::Duration loop; 
    } init_period; 
 
    init_period initp[] ={ 
        {"1min", one_min}, 
        {"5min", five_min}, 
        {"15min", fifteen_min}, 
        {"30min", therteen_min}, 
        {"1hour", one_hour},
	{"2hour", two_hour},
	{"1day", one_day},
	{NULL, one_hour}
    }; 

/** 
 * publier trame en ros	(Publisher "Topic" par capteur)
 * CAP_LIST : Vecteur sur la liste des capteurs existant (annuaire)
 * index du capteur dans l'annuaire correspond au même index de Publisher[]
 */

void publish_topics(int pub_id, std::string topic_name, ros::NodeHandle node, PALGATE_msgs::ZigbeeFrame msg){

   chatter_pub[pub_id] = node.advertise<PALGATE_msgs::ZigbeeFrame>(topic_name, 1000);
   ROS_INFO("capID %s, capLoc %s, sensvals %s", msg.capid.c_str(),msg.caplocation.c_str(),msg.sensvals.c_str());
   chatter_pub[pub_id].publish(msg);
      ros::spinOnce();
}

/** 
 * Callback
 * initialisation de la liste des publishers inactif pendant une periode T
 */
void init_caplist(const ros::TimerEvent& ){
   ROS_INFO("Initialisation des Publishers.......!");
	timer2.stop();
	for(int i=0; i<(int)CAP_LIST.size()+1; i++){
	chatter_pub[i].shutdown();	
	}
	//ros::spinOnce();
	timer2.start();

   ROS_INFO("Initialisation terminee *");
}

void leave(int sig);

int main(int argc, char **argv)
{

 (void) signal(SIGINT,leave);

/* zigbee_pub : nodename publisher_type initiasiaton_periode*/	

 if((argc != 2) && (argc != 3) && (argc != 4) ){
 printf("[ERROR ! ROS_ZIGBEE_PUBLISHER]\n");
 printf("Invalid command line! tape [help] for usage manuel.\n\n");
 }
 
 if(argc==2){
	if(strcmp(argv[1],"help")==0)
	help_function();
	else {
	 printf("[ERROR! Command line Structure]");
	printf("\nStructure:");
	printf("\n\t[Node_name] [Publisher_type: ALL | capID | locationID] [#Init_period: optionnal]\n\n");}
 }
 
 if((argc==3) || (argc==4)){

if(argc==4){
 int trouve = 0;
 init_period *p;
        for (p = initp; p->name; p++) { 
            if (strcmp(p->name, argv[3]) == 0) { 
                duration = p->loop; 
		trouve = 1;
		break;
            }
        }
if(trouve==0){
printf("[ERROR! Init_period]");
printf("\nAllowed value: 1min | 5min | 15min | 30min | 1hour | 2hour | 1day\n");
return 0;
}	
}

 if(strcmp(argv[2],"ALL")==0){
  std::stringstream pub;
  pub << node_name << "_" <<argv[1];
  printf("\nZigbee Publisher service started with this configuration: \n");
  std::cout<<"\t#Node name:             "<< pub.str() <<"\n";
  printf("\t#Publishers type:       ALL\n");
  printf("\t#Topic name:            zigbee_data");
  printf("\n--------------------\n");
  Publishmain_ALL(argc,argv); //pubish function
 }
 else if(strcmp(argv[2],"capID")==0){
  std::stringstream pub;
  pub << node_name << "_" <<argv[1];
  printf("\nZigbee Publisher service started with this configuration: \n");
  std::cout<<"\t#Node name:             "<< pub.str() <<"\n";
  printf("\t#Publishers type:       capID\n");
  printf("\t#Topics init period:    %d sec", duration.sec);
  printf("\n--------------------\n");
  Publishmain_By_CAPID(argc,argv);
 }
 else if(strcmp(argv[2],"locationID")==0){
  std::stringstream pub;
  pub << node_name << "_" <<argv[1];
  printf("\nZigbee Publisher service started with this configuration: \n");
  std::cout<<"\t#Node name:             "<< pub.str() <<"\n";
  printf("\t#Publishers type:       locationID\n");
  printf("\t#Topics init period:    %d sec", duration.sec);
  printf("\n--------------------\n");
  Publishmain_By_LOCATIONID(argc,argv);
 }  
 else {
  printf("[ERROR! Publisher_type]\n");
  printf("Publisher_type:  ALL | capID | locationID\n\n");
 }

}


  return 0;
}


void leave(int sig) {
        printf("\nInterrupted..\n");
        exit(sig);
}


/* publishe by capteurID */ 
void Publishmain_By_CAPID(int argc, char **argv){

/**
   * The ros::init() function needs to see argc and argv so that it can perform
   * any ROS arguments and name remapping that were provided at the command line. For programmatic
   * remappings you can use a different version of init() which takes remappings
   * directly, but for most command-line programs, passing argc and argv is the easiest
   * way to do it.  The third argument to init() is the name of the node.
   *
   * You must call one of the versions of ros::init() before using any other
   * part of the ROS system.
   */

/**Get Hostname
  int z;
  char hostname[32];
  z = gethostname(hostname, sizeof hostname);*/
	
  std::stringstream pub;
  pub << node_name << "_" <<argv[1];
  ros::init(argc, argv, pub.str());

  /**
   * NodeHandle is the main access point to communications with the ROS system.
   * The first NodeHandle constructed will fully initialize this node, and the last
   * NodeHandle destructed will close down the node.
   */
  ros::NodeHandle n;


  /*Période d'initialisation de la liste des Publisers ros::Duration(sec.nsec)*/
  timer2 = n.createTimer(duration, init_caplist); 

  /**
   * A count of how many messages we have sent. This is used to create
   * a unique string for each message.
   */
  int count = 0;
  init(); // Read the serial port

  
  while (1) //ros::ok()
  {
	
        getFrame(); // Get Frame
	ros::Time tstart = ros::Time::now();
        parseFrame(&strct_frame, &strct_mydataframe); // Parse Frame

	struct xbee_dataframe *p_sensorDataframe = &strct_mydataframe; 

	char text[120] ="";
	//int i;
	int j;

	for (j=0; j<=p_sensorDataframe->numberOfReadings; j++) {
		strcat(text,p_sensorDataframe->sensor[j].variableName);
		strcat(text,"#");
		strcat(text,p_sensorDataframe->sensor[j].variableValue);
		if(j != p_sensorDataframe->numberOfReadings)
		strcat(text,"#");
	}


    /**
     * This is a message object. You stuff it with data, and then publish it.
     */

    PALGATE_msgs::ZigbeeFrame msg;
    std::stringstream ss;
    std::stringstream capID;
    std::stringstream capLocation;
    ss <</*"Location#"<<p_sensorDataframe->location<<"#CapteurID#"<<p_sensorDataframe->iD<<"#"<<*/text;
    capID << p_sensorDataframe->iD;
    capLocation << p_sensorDataframe->location;
  
    msg.capid = capID.str();     
    msg.caplocation = capLocation.str();
    msg.sensvals = ss.str();

   // msg.frame_id = ss.str();
    msg.seq = count;
    msg.stamp = ros::Time::now();

   // ROS_INFO("%s", msg.frame_id.c_str());
 

    /**
     * Détectetion de nouveaux capteurs
     * Mettre à jours l'annuaire des capteurs
     * Publication dynamique des frames par capteurID
     */ 


	if( ((int)CAP_LIST.size()) == 0){ //inisialisation du vecteur
	CAP_LIST.push_back(p_sensorDataframe->iD); 	//Ajout du nouveau capteur dans l'annuaire

	std::stringstream name;
	name << "MADYNESGate/ZigbeeNode/cap"<<p_sensorDataframe->iD;

	publish_topics(0,name.str(), n ,  msg);
	//printf("Premier capteur ajouter %s\n",p_sensorDataframe->iD);
	}
	else {		//vérifier l'existance du capid
	it = std::find(CAP_LIST.begin(), CAP_LIST.end(),p_sensorDataframe->iD);
	
	if(it != CAP_LIST.end()){	//CAP existe
	size_t index = std::distance(CAP_LIST.begin(), it); 	//l'index du capteur dans l'annuaire
	
	std::stringstream name;
	name << "MADYNESGate/ZigbeeNode/cap"<<p_sensorDataframe->iD;

	publish_topics((int)index,name.str(), n , msg);
	}
	else {		//CAP doesn't exist
	CAP_LIST.push_back(p_sensorDataframe->iD); 	//Ajout du nouveau capteur dans l'annuaire

	std::stringstream name;
	name << "MADYNESGate/ZigbeeNode/cap"<<p_sensorDataframe->iD;

	publish_topics((int)CAP_LIST.size(),name.str(), n ,  msg); 
	}	
	
	}

	//TEMPS D'EXECUTION
	ros::Time tfin = ros::Time::now();
	ros::Duration def = tfin - tstart;
	ROS_INFO("Temps d'exec %ds, %dns",def.sec, def.nsec);


    ++count;
  }


}



/* publishe ALL */ 
void Publishmain_ALL(int argc, char **argv){

  std::stringstream pub;
  pub << node_name << "_" <<argv[1];
  ros::init(argc, argv, pub.str());

  ros::NodeHandle n;

  ros::Publisher chatter_pub = n.advertise<PALGATE_msgs::ZigbeeFrame>("zigbee_data", 1000);

   /**
   * A count of how many messages we have sent. This is used to create
   * a unique string for each message.
   */
  int count = 0;
  init(); // Read the serial port

  while (ros::ok()) //ros::ok()
  {

        getFrame(); // Get Frame
	
        parseFrame(&strct_frame, &strct_mydataframe); // Parse Frame
	
	struct xbee_dataframe *p_sensorDataframe = &strct_mydataframe; 

	char text[120] ="";
	//int i;
	int j;

	for (j=0; j<=p_sensorDataframe->numberOfReadings; j++) {
		strcat(text,p_sensorDataframe->sensor[j].variableName);
		strcat(text,"#");
		strcat(text,p_sensorDataframe->sensor[j].variableValue);
		if(j != p_sensorDataframe->numberOfReadings)
		strcat(text,"#");
	}


    /**
     * This is a message object. You stuff it with data, and then publish it.
     */

    PALGATE_msgs::ZigbeeFrame msg;

    std::stringstream ss;
    std::stringstream capID;
    std::stringstream capLocation;

    ss <<text;
    capID << p_sensorDataframe->iD;
    capLocation << p_sensorDataframe->location;
  
    msg.capid = capID.str();     
    msg.caplocation = capLocation.str();
    msg.sensvals = ss.str();

    msg.seq = count;
    msg.stamp = ros::Time::now();

    ROS_INFO("capID %s, capLoc %s, sensvals %s", msg.capid.c_str(),msg.caplocation.c_str(),msg.sensvals.c_str());

    chatter_pub.publish(msg);
    
    ros::spinOnce();

    ++count;
  }
}

void Publishmain_By_LOCATIONID(int argc, char **argv){
/**
   * The ros::init() function needs to see argc and argv so that it can perform
   * any ROS arguments and name remapping that were provided at the command line. For programmatic
   * remappings you can use a different version of init() which takes remappings
   * directly, but for most command-line programs, passing argc and argv is the easiest
   * way to do it.  The third argument to init() is the name of the node.
   *
   * You must call one of the versions of ros::init() before using any other
   * part of the ROS system.
   */

/**Get Hostname
  int z;
  char hostname[32];
  z = gethostname(hostname, sizeof hostname);*/
	
  std::stringstream pub;
  pub << node_name << "_" <<argv[1];
  ros::init(argc, argv, pub.str());

  /**
   * NodeHandle is the main access point to communications with the ROS system.
   * The first NodeHandle constructed will fully initialize this node, and the last
   * NodeHandle destructed will close down the node.
   */
  ros::NodeHandle n;


  /*Période d'initialisation de la liste des Publisers ros::Duration(sec.nsec)*/
  timer2 = n.createTimer(duration, init_caplist); 

  /**
   * A count of how many messages we have sent. This is used to create
   * a unique string for each message.
   */
  int count = 0;
  init(); // Read the serial port

  while (1) //ros::ok()
  {

        getFrame(); // Get Frame
	
        parseFrame(&strct_frame, &strct_mydataframe); // Parse Frame
	
	struct xbee_dataframe *p_sensorDataframe = &strct_mydataframe; 

	char text[120] ="";
	//int i;
	int j;

	for (j=0; j<=p_sensorDataframe->numberOfReadings; j++) {
		strcat(text,p_sensorDataframe->sensor[j].variableName);
		strcat(text,"#");
		strcat(text,p_sensorDataframe->sensor[j].variableValue);
		if(j != p_sensorDataframe->numberOfReadings)
		strcat(text,"#");
	}


    /**
     * This is a message object. You stuff it with data, and then publish it.
     */

    PALGATE_msgs::ZigbeeFrame msg;

    std::stringstream ss;
    std::stringstream capID;
    std::stringstream capLocation;

    ss <<text;
    capID << p_sensorDataframe->iD;
    capLocation << p_sensorDataframe->location;
  
    msg.capid = capID.str();     
    msg.caplocation = capLocation.str();
    msg.sensvals = ss.str();

    msg.seq = count;
    msg.stamp = ros::Time::now();

   // ROS_INFO("%s", msg.frame_id.c_str());
 

    /**
     * Détectetion de nouveaux capteurs
     * Mettre à jours l'annuaire des capteurs
     * Publication dynamique des frames par capteurID
     */ 


	if( ((int)CAP_LIST.size()) == 0){ //inisialisation du vecteur
	CAP_LIST.push_back(p_sensorDataframe->location); 	//Ajout du nouveau capteur dans l'annuaire

	std::stringstream name;
	name << "loc"<<p_sensorDataframe->location;

	publish_topics(0,name.str(), n ,  msg);
	//printf("Premier capteur ajouter %s\n",p_sensorDataframe->iD);
	}
	else {		//vérifier l'existance du capid
	it = std::find(CAP_LIST.begin(), CAP_LIST.end(),p_sensorDataframe->location);
	
	if(it != CAP_LIST.end()){	//CAP existe
	size_t index = std::distance(CAP_LIST.begin(), it); 	//l'index du capteur dans l'annuaire
	
	std::stringstream name;
	name << "loc"<<p_sensorDataframe->location;

	publish_topics((int)index,name.str(), n , msg);
	}
	else {		//CAP doesn't exist
	CAP_LIST.push_back(p_sensorDataframe->location); 	//Ajout du nouveau capteur dans l'annuaire

	std::stringstream name;
	name << "loc"<<p_sensorDataframe->location;

	publish_topics((int)CAP_LIST.size(),name.str(), n ,  msg); 
	}	
	
	}

    ++count;
  }

}


void help_function(){
printf("\n[ROS_ZIGBEE_PUBLISHER] Command Line Structure:\n");
printf("\nStructure:");
printf("\n\t[Node_name] [Publisher_type: ALL | capID | locationID] [#Init_period: optionnal]\n");
printf("\nCommands:");
printf("\n\t[Node_Name]         Name of the node publishing ZigBee Data.\n");
printf("\n\t[Publisher_type]    Type of publishing Topics of ZigBee Data:");
printf("\n\t                     - ALL :        One Topic containt all ZigBee Data.");
printf("\n\t                     - capID :      Dynamic Topic by capteur ID.");
printf("\n\t                     - locationID : Dynamic Topic by Location ID.\n");
printf("\n\t                    //Type [rostopic list -v] to print information about active topics\n");
printf("\n\t[#Init_period]      Period of initialising the list of the actif publishers (Topics)");
printf("\n\t                    unuseless with Publisher_type: ALL.\n");
printf("\n\t                    Allowed period value:");
printf("\n\t                    1min | 5min | 15min | 30min | 1hour | 2hour | 1day.\n");
printf("\n\tAuthor:	Moutie CHEHAIDER\n");
}




