#ifndef __SCOREDB__
#define __SCOREDB__
#include <fstream>
#include <vector>

struct ROW
{
    int row_number;
    std::string name;
    std::string score;
    std::string date;
};

const int NAMECOLWIDTH = 10;
const int SCORECOLWIDTH = 11;
const int DATECOLWIDTH = 11;
const int ROW_SIZE = 38;



class ScoreDataBase
{
public:
    ScoreDataBase(const std::string file_name = "sanke_scores.txt");
    ~ScoreDataBase();
    ScoreDataBase(const ScoreDataBase& other_) = delete;
    const ScoreDataBase& operator=(const ScoreDataBase& other_) = delete;
    void WriteToDB(ROW& data_);
    std::string ReadFromDB(int row_number);
    std::vector<ROW> GETScoreTable();
    void ToBuffer(ROW& data_, std::string& str);
    ROW FromBuffer(char *buffer);
    static const std::string CurrentDateNTime();
private:
    std::string m_file_name;
    int m_name_col_width;
    int m_score_col_width;
    int m_date_col_width;
    int m_row_size;
};

#endif /* __SCOREDB__ */