#include <iostream>
#include <map>
#include "score_database.hpp"


void PrintFivaHighestScores(ScoreDataBase& db, std::vector<ROW>& vec)
{
    std::multimap<int, int, std::greater<int>> scores;
    for (ROW row : vec)
    {
        scores.insert(std::pair(std::stoi(row.score), row.row_number));
    }

    auto iter = scores.begin();
    int range = scores.size() > 5 ? 5 : scores.size();
    for (int i = 0; i < range; ++i)
    {
        std::cout<<db.ReadFromDB(iter->second)<<std::endl;
        ++iter;
    }
}

int main()
{
    ScoreDataBase db;
    ROW data;
    data.date = ScoreDataBase::CurrentDateNTime();
    data.name = "Test3";
    data.score = "85";
    db.WriteToDB(data);
    std::cout<<db.ReadFromDB(1)<<std::endl;;
    std::vector<ROW> vec = db.GETScoreTable();
    PrintFivaHighestScores(db, vec);

    return 0;
}