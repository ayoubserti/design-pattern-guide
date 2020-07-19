/*
* Decorator design pattern
*/

#include <string>
#include <iostream>
#include <memory>

using std::string;
using std::shared_ptr;

class IGenerator{
    
public:
    virtual   void generate( const string& filename) = 0;
};

class DocGenerator : public IGenerator{

    public:
    void generate ( const string& filename) override {
        std::cout << "Generating Docx for " << filename << std::endl;
    }

};

class GeneratorDecorator : public IGenerator{
    
    shared_ptr<IGenerator> wrappee_;

public:
    GeneratorDecorator(shared_ptr<IGenerator> wrappee)
    :wrappee_(wrappee){}

    void generate(const string& filename ) override{
        // post or pre generation
        wrappee_->generate(filename);
        _generate(filename);
    }

    virtual ~GeneratorDecorator() {}
protected:
   virtual void  _generate( const string& filename) = 0; // pure virtual function: uncomplet type

};

//Mardown generator
class MarkDownGenerator : public GeneratorDecorator{

public:
  explicit   MarkDownGenerator( shared_ptr<IGenerator> wrappee )
                :GeneratorDecorator(wrappee){}

    protected:
    void  _generate( const string& filename) override{
        std::cout << "MarkDown generator of file " << filename << std::endl;
    }
};

//pdf generator
class PDFDownGenerator : public GeneratorDecorator{

public:
  explicit   PDFDownGenerator( shared_ptr<IGenerator> wrappee )
                :GeneratorDecorator(wrappee){}

    protected:
    void  _generate( const string& filename) override{
        std::cout << "PDF generator of file " << filename << std::endl;
    }
};


//epub generator
class EPUBDownGenerator : public GeneratorDecorator{

public:
  explicit   EPUBDownGenerator( shared_ptr<IGenerator> wrappee )
                :GeneratorDecorator(wrappee){}

    protected:
    void  _generate( const string& filename) override{
        std::cout << "Epub generator of file " << filename << std::endl;
    }
};


//client code
int main ( int argc, char** argv){

    {
        //previously code:
        shared_ptr<DocGenerator> docGenerator( new DocGenerator());
        docGenerator->generate("myFile.csv");
    }
    
    std::cout << "---------------------------------------" << std::endl;
     //current code
    shared_ptr<IGenerator> 
        docGenerator( new DocGenerator()),
        markdownGen( new MarkDownGenerator(docGenerator)),
        pdfGen ( new PDFDownGenerator(markdownGen)),
        epubGen ( new EPUBDownGenerator(pdfGen));

    //calling epubGen is like calling every single generator 
    epubGen->generate("myFile.csv");
    
    return 0;
}