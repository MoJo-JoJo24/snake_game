#include <strings.h>
#include <string.h>

#include <score_database.hpp>

ScoreDataBase::ScoreDataBase(const std::string file_name): m_file_name(file_name),
m_name_col_width(26), m_score_col_width(16), m_date_col_width(26), 
m_row_size(m_name_col_width + m_score_col_width + m_date_col_width + 2)
{
    std::ifstream file_handle(file_name, std::ios_base::in);
    if (!file_handle.is_open())
    {
        std::ofstream tmp_file_handle(file_name);
        tmp_file_handle.close();
        file_handle.open(file_name, std::ios_base::in);
        if (!file_handle.is_open())
        {
            throw std::runtime_error("Failed to Open File!");
        }
    }

    char *buf = new char [m_row_size];
    file_handle.seekg(0, std::ios::beg);
    file_handle.read(buf, m_row_size);
    file_handle.close();
    if ('N' != *buf)
    {
        ROW line;
        line.name = "NAME";
        line.score = "SCORE";
        line.date = "DATE";
        WriteToDB(line);
    }
    
    delete [] buf; 
}

ScoreDataBase::~ScoreDataBase()
{}

const std::string ScoreDataBase::CurrentDateNTime()
{
    time_t t = time(NULL);
    
    return std::string(asctime(localtime(&t)));
}

void ScoreDataBase::WriteToDB(ROW& data_)
{
    std::string buffer;

    ToBuffer(data_, buffer);

    std::ofstream file_handle(m_file_name, std::ios_base::out | std::ios_base::app);
    
    if (!file_handle.is_open())
    {
        throw std::runtime_error("Failed to Open File!");
    }    

    file_handle.write(buffer.c_str(), buffer.size());
    file_handle.close();
}

void ScoreDataBase::ToBuffer(ROW& data_, std::string& str)
{
    int name_size = data_.name.size();
    int score_size = data_.score.size();
    int date_size = data_.date.size();

    int range = m_name_col_width - (name_size - 1);
    range = range > 0 ? range : 0;
    for (int i = 0; i < range; ++i)
    {
        data_.name += " ";
    }
    
    auto iter = data_.name.end();
    --iter;
    *iter = ',';

    for (int i = 0; i < m_score_col_width - (score_size - 1); ++i)
    {
        data_.score += " ";
    }
    
    iter = data_.score.end();
    --iter;
    *iter = ',';

    iter = data_.date.end();
    --iter;
    if (*iter == '\n')
    {
        data_.date.erase(iter);
    }

    for (int i = 0; i < m_date_col_width - (date_size - 1); ++i)
    {
        data_.date += " ";
    }

    iter = data_.date.end();
    --iter;
    *iter = '\n';
    
    str.swap(data_.name);
    str.append(data_.score);
    str.append(data_.date);
}

std::string ScoreDataBase::ReadFromDB(int row_number)
{
    std::ifstream file_handle(m_file_name, std::ios_base::in);
    if (!file_handle.is_open())
    {
        throw std::runtime_error("Failed to Open File!");
    }
    char *buf = new char [m_row_size];
    file_handle.seekg(m_row_size * (row_number - 1), std::ios::beg);
    file_handle.read(buf, m_row_size);
    file_handle.close();

    std::string row(buf);
    delete [] buf;

    return row;
}

static int GetLengthOfFile(std::ifstream& file_handle)
{
    file_handle.seekg(0, file_handle.end);
    int length = file_handle.tellg();
    file_handle.seekg (0, file_handle.beg);

    return length;
}

std::vector<ROW> ScoreDataBase::GETScoreTable()
{
    std::ifstream file_handle(m_file_name, std::ios_base::in);
    if (!file_handle.is_open())
    {
        throw std::runtime_error("Failed to Open File!");
    }

    std::vector<ROW> res;
    int length = GetLengthOfFile(file_handle);

    char *buf = new char [m_row_size];
    char *head = buf;
    int ctr = 2;
    for (int i = m_row_size; i < length - m_row_size; i += m_row_size, ++ctr)
    {
        bzero(buf, m_row_size);
        file_handle.seekg(i, std::ios::beg);
        file_handle.read(buf, m_row_size);
        ROW line = FromBuffer(buf);
        line.row_number = ctr;

        res.push_back(line);
    }

    file_handle.close();
    delete [] head;

    return res;
}


ROW ScoreDataBase::FromBuffer(char *buffer)
{
    char *end = buffer + m_row_size;
    char *word_boundary = strchr(buffer, ' ');
    char *tmp = buffer;
    ROW line;
    
    line.name = *tmp;
    ++tmp;
    while (tmp != word_boundary)
    {
        line.name += *tmp;
        ++tmp;
    }
    word_boundary = strchr(tmp, ',');
    tmp = word_boundary;
    ++tmp;
    word_boundary = strchr(tmp, ' ');
    line.score = *tmp;
    ++tmp;
    while (tmp != word_boundary)
    {
        line.score += *tmp;
        ++tmp;
    }

    word_boundary = strchr(tmp, ',');
    tmp = word_boundary;
    ++tmp;
    line.date = *tmp;
    ++tmp;    

    while (tmp != end)
    {
        line.date += *tmp;
        ++tmp;
    }

    return line;
}