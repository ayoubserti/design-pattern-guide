/*
* Chain of Responsibility Design pattern 
*/

#include <iostream>
#include <memory>
#include <string>

using std::shared_ptr;
using std::string;

class Request
{

    string name_;
    bool   answered_;
public:
    Request ( const string& name) 
     :name_(name)
     ,answered_(false)
     {}    
     
    const string& get_name(){ return name_;}
    void answerIt() { answered_ = true;}
     
};

/**
 * Interface IHandler
*/
class IHandler
{
public:
    
    virtual void setNext( shared_ptr<IHandler> nextHandler) = 0;
    virtual void handle( shared_ptr<Request> request ) = 0;
};

/**
 * basic Request Handler
*/
class RequestHandler : public IHandler
{
    shared_ptr<IHandler> next_handler_;
    
public:

    RequestHandler(): next_handler_(nullptr){}
     
     void setNext ( shared_ptr<IHandler> next) override{
         next_handler_ = next;
     }

    virtual void handle (shared_ptr<Request> request) override { 
        if ( next_handler_ != nullptr)
            next_handler_->handle(request);
     }

};


/*
*  "http" request handler
*/
class HTTPRequestHandler : public RequestHandler
{
        using parent=RequestHandler;
  public:

      void handle( shared_ptr<Request> request ) override{
        if ( (request->get_name() == "http") || (request->get_name() == "soap") )
        {
            // it's an http request handle it 
            std::cout<< "We are handling Http request here" << std::endl;
            request->answerIt();
        }
        parent::handle(request);
        
      }
};

/*
*   "soap" request handler
*/

class SOAPRequestHandler :public RequestHandler
{
    using parent=RequestHandler;
    public:
    
    void handle( shared_ptr<Request> request ) override
    {
        if ( request->get_name() == "soap")
        {
            std::cout << "We are handling soap request" << std::endl;
            // SOAP is also HTTP
        }
        parent::handle(request);
        
    }

};

class SQLRequestHandler : public RequestHandler 
{
    using parent=RequestHandler;
public:

    void handle( shared_ptr<Request> request ) override
    {
        if ( request->get_name() == "sql")
        {
            std::cout << "We are handling SQL request" << std::endl;
            request->answerIt();
        }
        parent::handle(request);
        
    }
    
};

int main ( int argv , char ** argc)
{
    shared_ptr<Request> httpRequest = std::make_shared<Request>("http"),
                        soapRequest = std::make_shared<Request>("soap"),
                        sqlRequest = std::make_shared<Request>("sql");

    shared_ptr<IHandler> mainHandler( new HTTPRequestHandler()),
                         handler2 ( new SOAPRequestHandler()),
                         handler3 ( new SQLRequestHandler());

    mainHandler->setNext(handler2);
    handler2->setNext(handler3);

    //the order of chainned handler isn't so importante in our case

    mainHandler->handle(httpRequest);
    mainHandler->handle(soapRequest);
    mainHandler->handle(sqlRequest);

    return 0;
}
