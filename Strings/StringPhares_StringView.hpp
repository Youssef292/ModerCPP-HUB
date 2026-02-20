#include <iostream>
#include <string>
#include <unordered_map>
#include <string_view>
class CCommandParser
{


    public:
    CCommandParser(std::string_view command): m_command(command)
    {
        parseCommand();
    }

    
    
    std::string_view getArguments(std::string_view key);

    bool hasArgument(std::string_view key);


    private:
    std::string_view m_command;
    std::unordered_map<std::string_view,std::string_view> arguments;

    void parseCommand();
    

};

void CCommandParser::parseCommand()
{
    std::cout << "Paresing Command :" << m_command <<std::endl;


    size_t searchPos = 0;
    while(true)
    {
        size_t dahPos = m_command.find("--",searchPos);

        if(dahPos == std::string_view::npos) 
        break;

        //move to the key after --
        size_t keyPos = dahPos + 2;

        //search for the = position 
        size_t equalPos = m_command.find("=",keyPos);

        if(equalPos == std::string_view::npos)
        break;

        //Extract key 
        std::string_view key = m_command.substr(keyPos, equalPos - keyPos);

        //find value 
        size_t valuePos = equalPos + 1;
        size_t spacePos = m_command.find(' ',valuePos);

        std::string_view value;

        if(spacePos == std::string::npos)
        {
            value = m_command.substr(valuePos);
            searchPos = m_command.size();
        }
        else
        {
            value = m_command.substr(valuePos,spacePos - valuePos);
            searchPos = spacePos;
        }

        arguments.insert({key,value});








    }
}


std::string_view CCommandParser::getArguments(std::string_view key)
{
    auto it  = arguments.find(key);
    if( it !=  arguments.end())
    {
        return it->second;
    }

    return {};
}

bool CCommandParser::hasArgument(std::string_view key)
{
    return arguments.find(key) != arguments.end();
} 


int CommandParser_main(void)
{
    std::cout<< "==== String Parsing and Manipulation === " << std::endl;
    
    std::string cmd = "build --output=/bin/app --config=/etc/app.conf --debug=true";
    CCommandParser parser(cmd);


    std::cout <<"\n -- Extracting Parameters ---"<<std::endl;
    std::cout <<"Output: " << parser.getArguments("output") << std::endl;
    std::cout <<"Config: " << parser.getArguments("config") << std::endl;
    std::cout <<"Debug: " << parser.getArguments("debug") << std::endl;

    return 0;

    

}