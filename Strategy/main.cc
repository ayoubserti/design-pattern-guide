/**
 * Design Pattern `Strategy`
 * */

#include <iostream>
#include <memory>

//Insterface Strategy
class IStrategy
{

public:
    /**
     * @function add
     * @abstract excute the algorithm/strategy 
    */
    virtual uint32_t add(uint32_t a, uint32_t b) = 0; 
};

class SimpleSumStrategy : public IStrategy
{
public:

    uint32_t add(uint32_t a, uint32_t b) {
        return a+b;
    } 
};

class BitWiseSumStrategy : public IStrategy
{
    public:
    uint32_t add( uint32_t a , uint32_t b){
         uint32_t r ,c, mask;
   
    
         c =a & b; //first calculate initial carry 
         r = a ^ b;  //initial value of result; we use xor as it's a binary addition
          while(c != 0)
            {
                mask = c << 1;  //compute new mask by shifting the carry.
                c = r & mask;   // recompute the carry 
                r = r ^ mask;   // recompute the result
            } 
        return r;
    }
};

class Context 
{
    std::shared_ptr<IStrategy> current_strategy_;
public:
    void setStrategy(std::shared_ptr<IStrategy> strategy){
        current_strategy_ = strategy;
    }
    void calculate( uint32_t a , uint32_t b) {
        std::cout << "a + b = " ;
        std::cout << current_strategy_->add(a, b) << std::endl;
    }
};



int main(int argv, char** argc ){

    std::shared_ptr<IStrategy> simplesum ( new SimpleSumStrategy());
    std::shared_ptr<IStrategy> bitwisesum ( new BitWiseSumStrategy());

    Context ctx;
    ctx.setStrategy(simplesum);
    ctx.calculate(12,13);


    ctx.setStrategy(bitwisesum);
    ctx.calculate(1209872,13165233);
    
    return 0;
}
