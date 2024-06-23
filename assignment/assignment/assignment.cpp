//***************************************BASIL MUSTAFA ALKHUSHEINY********************************************
//***************************************          146790         ********************************************
//***************************************      PROJECT 1 OF OS    ********************************************

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


class Process
{
    string nameOfProcess;
    double arrivalTime;
    double processTime;

public:

    double delay, response, turnaround;

    Process()
    {
        nameOfProcess = "";
        arrivalTime = -1;
        processTime = -1;

    }

    Process(string nameOfProcess, double arrivalTime, double processTime)
    {
        this->nameOfProcess = nameOfProcess;
        this->arrivalTime = arrivalTime;
        this->processTime = processTime;

    }





    void SetNameOfProcess(string nameOfProcess) { this->nameOfProcess = nameOfProcess; }
    
    string GetNameOfProcess()  { return this->nameOfProcess; }


    void SetarrivalTime(int arrivalTime)   { this->arrivalTime = arrivalTime; }

    int  GetarrivalTime()  { return this->arrivalTime; }
    


    void SetprocessTime(int processTime) { this->processTime = processTime; }
    
    int  GetprocessTime()  { return this->processTime; }
    


    void Print()
    {
        cout << nameOfProcess << "---" << arrivalTime << "---" << processTime << endl;
    }

   


};












bool compareArrival( Process& ihs,  Process& rhs)
{
    return ihs.GetarrivalTime() < rhs.GetarrivalTime();
}


bool compareProcess(Process& ihs, Process& rhs)
{
    return ihs.GetprocessTime() < rhs.GetprocessTime();
}












int main()
{
   
    double numberOfProcesses;
    string nameOfProcess;
    double arrivalTime;
    double processTime;
    vector<Process> arrayOfProcess;
    vector<Process> waitArray;
    


    ifstream ifile;
    ifile.open("process test.txt",ios::in);
    ofstream ofile("final output.txt");




    ifile >> numberOfProcesses;

    while (!ifile.eof())
    {
        ifile >> nameOfProcess>>arrivalTime>>processTime;

        Process p (nameOfProcess, arrivalTime, processTime);

        arrayOfProcess.push_back(p);  
    }

    ifile.close();

    sort(arrayOfProcess.begin(), arrayOfProcess.end(), &compareArrival);


    


    double index = 0;
    double i2;
    double count = 0;
    vector<string> names;

    for (auto i = 0;; i++)
    {
        i2 = i;
        i += arrayOfProcess[index].GetprocessTime();
        arrayOfProcess[index].turnaround = i - arrayOfProcess[index].GetarrivalTime();
        arrayOfProcess[index].delay= arrayOfProcess[index].turnaround- arrayOfProcess[index].GetprocessTime();
        arrayOfProcess[index].response = arrayOfProcess[index].delay;





        ofile << arrayOfProcess[index].GetNameOfProcess() << ": (response=" << arrayOfProcess[index].response << ", turnaround=" << arrayOfProcess[index].turnaround << ", delay=" << arrayOfProcess[index].delay << ")\n";
        names.push_back(arrayOfProcess[index].GetNameOfProcess());




        for (auto j = i2 + 1; j <= i; j++)
        {
            for (auto v : arrayOfProcess) 
            {
                if (v.GetarrivalTime() == j)
                    waitArray.push_back(v);
            }

        }



        


        if (waitArray.size() > 0)
        {
            auto longProcessingTime = max_element(waitArray.begin(), waitArray.end(), &compareProcess);

            for (auto x = 0; x < arrayOfProcess.size(); x++)
            {
                if (longProcessingTime->GetNameOfProcess() == arrayOfProcess[x].GetNameOfProcess())
                {
                    string name = arrayOfProcess[x].GetNameOfProcess();
                    index = x; 

                    waitArray.erase(remove_if(waitArray.begin(), waitArray.end(),
                        [&](Process& s) {return s.GetNameOfProcess() ==name; }),waitArray.end());

                    /*for (auto v = waitArray.begin(); v != waitArray.end(); )
                        if (v->GetNameOfProcess() == arrayOfProcess[x].GetNameOfProcess())
                            waitArray.erase(v);*/

                    break;
                }

            }

        }

        



        count++;
        if (count >= numberOfProcesses)
            break;
        i--;



        
    }


    for (auto p : names)
        ofile << p;

    ofile.close();
   

    
    return 0;
}
















