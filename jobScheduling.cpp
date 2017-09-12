/*
 * Schedules jobs in order to minimize the weighted sum of completion times
 */
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

struct Job
{
    int weight;
    int length;
    double score;

    Job(int w, int l) : weight(w), length(l), score(0) { }
};

void assignDiffScores(vector<Job>& jobs)
{
    for (auto &i : jobs)
        i.score = i.weight - i.length;
}

void assignRatioScores(vector<Job>& jobs)
{
    for (auto &i : jobs)
        i.score = i.weight / double(i.length);
}

bool sortByScore(const Job &i, const Job &j)
{
    if (i.score == j.score)
        return i.weight >= j.weight;
    return i.score > j.score;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cout << "Usage: ./jobScheduling 'testfile' '0 = assign scores based on difference, 1 = assign scores based on ratio'" << endl;
        return -1;
    }

    ifstream fin(argv[1]);
    if (!fin.is_open())
        return -1;

    int n = 0;
    fin >> n;

    vector<Job> jobs;
    while (n--)
    {
        int w = 0, l = 0;
        fin >> w >> l;
        jobs.push_back(Job(w, l));
    }
    
    if (atoi(argv[2]) == 1)
        assignDiffScores(jobs);
    else
        assignRatioScores(jobs);
    sort(jobs.begin(), jobs.end(), sortByScore);
    
    long long int weightedSum = 0;
    int completionTime = 0;
    for (int i = 0; i < jobs.size(); ++i)
    {
        completionTime += jobs[i].length;
        weightedSum += completionTime * jobs[i].weight;
    }

    cout << "Schedule: " << endl;
    for (auto i: jobs)
        cout << i.weight << " " << i.length << endl;
    cout << "Weighted sum of completion times: " << weightedSum << endl;
    
    return 0;
}
