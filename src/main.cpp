#include "motion_state.h"
#include <iostream>
using namespace std;

int main()
{
    MotionState ms;
    ms.setup_connect(2700,"192.168.125.1");
    vector<float> current_state(7);
    ms.get_current_state(2,current_state);

    cout<<current_state[0]<<" "<<current_state[1]<<" "<<current_state[2]<<" "<<current_state[3]<<" "<<current_state[4]<<" "<<current_state[5]<<" "<<current_state[6]<<endl;

    cout<<"please input o to move to target"<<endl;

    vector<float> target_pose=current_state;

    string temp;
    cin>>temp;
    while(temp=="o")
    {
        bool move_res=ms.set_move_request(1,target_pose);
        if(move_res)
        {
            cout<<"have moved finished!"<<endl;
        }
    }

    ms.close_connect();
    return 0;
}
