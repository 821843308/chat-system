#include "data.h"

data::data()
{}
data::~data()
{}
void data::serialize(std::string &output)
{
    Json::Value value;
    value["name"] = name;
    value["school"] = school;
    value["msg"] = msg;
    value["cmd"] = cmd;

    Json::FastWriter writer;
    output = writer.write(value);
    return;
}

void data::unserialize(std::string &input)
{
    Json::Value value;
    Json::Reader reader;
    reader.parse(input,value);
    name = value["name"].asString();
    school = value["school"].asString();
    msg = value["msg"].asString();
    this->cmd = value["cmd"].asString();

}

/* int main() */
/* { */
/*     data d; */
/*     data out; */
/*     std::string jsonstring; */
/*     d.name = "rbl"; */
/*     d.school = "sust"; */
/*     d.msg = "nihao"; */
/*     d.cmd = "qiut"; */
/*     d.serialize(jsonstring); */

/*     std::cout<<jsonstring<<std::endl; */
    
/*     out.unserialize(jsonstring); */
/*     std::cout<<out.name<<std::endl; */
/*     std::cout<<out.school<<std::endl; */
/*     std::cout<<out.msg<<std::endl; */
/*     std::cout<<out.cmd<<std::endl; */

/*     return 0; */
/* } */
