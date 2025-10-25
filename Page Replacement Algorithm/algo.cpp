#include <iostream>
#include <vector>
using namespace std;
#define MAX 100

bool present(vector<int>& frames, int f, int page){
    for(int i = 0 ; i < f ; i++){
        if(frames[i]==page){
            return true;
        }
    }
    return false;
}

void FIFO(vector<int> frames, int n , vector<int>& pages){
    cout << "Implementing FIFO .....\n";
    int ptr = 0;
    int hit = 0;
    int fault = 0;
    int s = frames.size();
    for(int i = 0 ; i < n ; i++){
        int page = pages[i];
        if(present(frames,s,page)){
            hit = 1;
        }
        if(hit){
            cout << "HIT for page : "<< page << endl;
            hit = 0;
        }else{
            cout << "Page Fault occured for page : "<< page << endl;
            fault++;
            frames[ptr]=page;
            ptr = (ptr+1)%s;
        }
    }
    cout << "Total page faults : " << fault << endl;
    cout << "Fault ratio : "<< (float)fault/(float)n << endl;
    cout << "Hit ratio : "<< (float)(n-fault)/(float)n << endl;
}

void LRU(vector<int> frames, int n , vector<int>& pages){
    int t = 0;
    int fault = 0;
    int hit = 0;
    cout << "USING LRU ......\n";
    int f = frames.size();
    vector<int> time(f,0);
    for(int i = 0 ; i < n ; i++){
        t++;
        int page = pages[i];
        int idx = -1;
        for(int j = 0 ; j < f ; j++){
            if(frames[j]==page){
                idx = j;
                hit = 1;
            }
        }
        if(hit){
            cout << "Hit for page : "<< page << endl;
            time[idx]=t;
            hit = 0;
            continue;
        }

        int mini = 100000000;
        for(int j = 0 ; j<f ; j++){
            if(time[j] < mini){
                mini = time[j];
                idx = j;
            }
        }
        frames[idx]=page;
        time[idx]=t;
        cout << "Page Fault occured for page : "<< page << endl;
        fault++;        
    }
    cout << "Total page faults : " << fault << endl;
    cout << "Fault ratio : "<< (float)fault/(float)n << endl;
    cout << "Hit ratio : "<< (float)(n-fault)/(float)n << endl;
}

void Optimal(vector<int> frames, int n , vector<int>& pages){
    cout << "Using Optimal Algorithm : \n";
    int f = frames.size();
    int faults = 0;
    for(int i = 0 ; i < n ; i++){
        int idx = -1;
        int page = pages[i];
        int hit = 0;
        for(int j = 0 ; j < f ; j++){
            if(frames[j]==page){
                cout << "HIT for page : "<< page<<endl;
                hit = 1;
                break;
            }
        }
        if(hit){ hit = 0; continue;}
        int far = -1;
        for (int j = 0 ; j < f ; j++){
            //checking frame
            if(frames[j]==-1){
                idx = j;
                break;
            }
            int nextUse = -1;
            for(int k = 0 ; k < n ; k++){
                if(pages[k]==frames[j]){
                    nextUse = k;
                    break;
                }
            }
            if(nextUse == -1 ){
                // page never used again
                idx = j; break;
            }
            if(nextUse > far){
                far = nextUse;
                idx = j;
            }
        }
        frames[idx]=page;
        faults ++;
    }
    cout << "Total page faults : " << faults << endl;
    cout << "Fault ratio : "<< (float)faults/(float)n << endl;
    cout << "Hit ratio : "<< (float)(n-faults)/(float)n << endl;
}


int main(){
    int n , no_of_frames;
    cout << "Enter number of pages : ";
    cin >> n;
    vector<int> pages(n);
    for(int i = 0 ; i < n ; i++){
        cin >> pages[i];
    }
    cout << "\nEnter size of frames : ";
    cin >> no_of_frames;
    vector<int> frames(no_of_frames,-1);
    FIFO(frames,n,pages);
    LRU(frames,n,pages);
    Optimal(frames,n,pages);
}


