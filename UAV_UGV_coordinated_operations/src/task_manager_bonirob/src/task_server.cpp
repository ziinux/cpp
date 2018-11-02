#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#include "task_manager_lib/TaskServerDefault.h"

#include "task_manager_bonirob/BonirobEnv.h"


using namespace task_manager_bonirob;
using namespace task_manager_lib;

class TaskServer : public TaskServerBase {
    public:
        TaskServer(TaskEnvironmentPtr _env) : TaskServerBase(_env,true) {
            start();
        }

};

int main(int argc, char *argv[])
{
    ros::init(argc,argv,"bonirob_tasks");//init ros
    ros::NodeHandle nh("~");
    TaskEnvironmentPtr env(new BonirobEnv(nh)); // Change this to your environment
    TaskServer ts(env);
    ros::spin();
    return 0;
}
