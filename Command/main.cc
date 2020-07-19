#include <iostream>
#include <memory>
#include <string>


using std::string;
using std::shared_ptr;

class ICommand
{
public:
    virtual void execute() = 0;
};


class SimpleCmd : public ICommand
{
    const string name_;
public:
    SimpleCmd (const string& name)
    :name_(name){}
    void execute() override{
        std::cout << "Executing SimpleCmd: " << name_ << std::endl;
    }
};

class Invoker 
{
    shared_ptr<ICommand>   start_cmd_;
    shared_ptr<ICommand>   finish_cmd_;
public:

    enum CmdType{
        eStart,
        eFinish
    };

    void   setCmd(CmdType type, std::shared_ptr<ICommand> cmd){ 
        if ( type == CmdType::eStart)
            start_cmd_ = cmd;
        else if ( type == CmdType::eFinish)
            finish_cmd_ = cmd;    
    }
    
    void executeCommand ( CmdType type){
        if ( (type== eStart) && (start_cmd_ != nullptr))
            start_cmd_->execute();
          if ( (type== eFinish) && (finish_cmd_ != nullptr))
            finish_cmd_->execute();
    }
};

//Receiver is the concrete executor of the command
class Receiver 
{
public:
    void doComplexTask1( string param) {
        std::cout << "Wait until task 1 is done using param " << param << std::endl;
    }

    void doComplexTask2( string param) {
        std::cout << "Wait until task 2 is done using param " << param << std::endl;
    }
};

class ComplexCmd : public ICommand
{
    shared_ptr<Receiver> receiver_;
    string param1_;
    string param2_;

public:
    ComplexCmd( shared_ptr<Receiver> receiver , const string& param1, const string& param2)
    :receiver_(receiver)
    ,param1_(param1)
    ,param2_(param2)
    {}
    void execute() override{
        std::cout << "Executing ComplexCmd " << std::endl;
        receiver_->doComplexTask1( param1_);
        receiver_->doComplexTask2( param2_);
    }
};




int main(int argc, char** argv){
    
    shared_ptr<ICommand> simplecmd1( new SimpleCmd("Dummy"));

    shared_ptr<Receiver> receiver( new Receiver());
    shared_ptr<ICommand> complexcmd ( new ComplexCmd(receiver, "Foo", "Bar"));
    shared_ptr<Invoker> invoker( new Invoker());

    invoker->setCmd(Invoker::eStart,simplecmd1);
    invoker->setCmd(Invoker::eFinish, complexcmd);

    invoker->executeCommand(Invoker::eStart);
    invoker->executeCommand(Invoker::eFinish);

    return 0;
}