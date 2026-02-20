#include <iostream>
#include <string>
#include <vector>
class CommandParser 
{

    public:
    CommandParser(std::string &command) :
    m_command(command) {ParseCommand();}

    void ParseCommand();
    std::string getArgument(const std::string &key);
    bool  hasArguments(const std::string &key);
    



    private:
    std::string m_command;
    std::vector<std::pair<std::string, std::string>> arguments;

};

void CommandParser::ParseCommand()
{
        std::cout<< "Paresing:" << m_command <<std::endl;

        auto pos = 0;
        while(pos < m_command.size())
        {
            pos = m_command.find("--",pos);
            if(pos == std::string::npos) break;

            /**
             * Extract Key and Values from the command 
             */
            auto equation_pos = m_command.find('=',pos);
            auto spaces_pos = m_command.find(' ',pos);

            if(equation_pos != std::string::npos){
                std::string key = m_command.substr(pos + 2, equation_pos - pos - 2); // Extract the key after --
                auto end = 0;
                if(spaces_pos != std::string::npos)
                {
                    end = spaces_pos;
                }else {end = m_command.size();}


                std::string value = m_command.substr(equation_pos +1 , end - equation_pos -1);
                
                arguments.push_back({key,value});
                std::cout<<"Found: " << key << " = " << value << std::endl; 

                pos = end;


            }else{pos++;}


        }


}


std::string CommandParser::getArgument(const std::string &key)
{
    for(const auto &arg : arguments){
        if(arg.first == key) 
        {
            return arg.second;
        }
    }
    return "";

}


bool CommandParser::hasArguments(const std::string &key)
{
    return !getArgument(key).empty();
}


int CommandParser_main(void)
{
    std::cout<< "==== String Parsing and Manipulation === " << std::endl;
    
    std::string cmd = "build --output=/bin/app --config=/etc/app.conf --debug=true";
    CommandParser parser(cmd);


    std::cout <<"\n -- Extracting Parameters ---"<<std::endl;
    std::cout <<"Output: " << parser.getArgument("output") << std::endl;
    std::cout <<"Config: " << parser.getArgument("config") << std::endl;
    std::cout <<"Debug: " << parser.getArgument("debug") << std::endl;

    return 0;

    

}