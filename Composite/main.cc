/*
* Composite Design pattern
* I pick the problem described in book 'Dive Into Design Patterns' 
* The problem of order receipt's
*/

#include <iostream>
#include <vector>
#include <memory>
#include <numeric>

using std::vector;
using std::shared_ptr;

class IOrderComponent
{

public:
    virtual uint32_t getPrice() = 0; 
};

class OrderBox : public IOrderComponent
{
    vector<shared_ptr<IOrderComponent> > children_;
public:
    
    uint32_t getPrice() override{
        uint32_t result = 0;
        for (auto&& it :  children_){
            result+= it->getPrice();
        }
        return result;
    }

    void add (shared_ptr<IOrderComponent> comp) {
        children_.push_back(comp);
    }
    void remove(shared_ptr<IOrderComponent> comp){
        //naive implementation of remove. Maybe you want to use a custom 
        //comparator function
        //we may also check sub-box
        auto it = std::find(children_.begin(), children_.end(),comp); 
        if ( it != children_.end())
            children_.erase(it);
    }

    auto getChildren (){
        return children_;
    }

};

class Product : public IOrderComponent
{
    uint32_t    price_;
public:
    Product( uint32_t price ) 
        :price_(price){}

    uint32_t getPrice() override {
        return price_;
    }

};


int main( int argv , char** argc){

    //client function
    //prepare our products
    vector<uint32_t> prices{23,76, 98, 76 ,93, 76};
    vector<shared_ptr<IOrderComponent> > products;
    for ( auto&& it : prices)
        products.push_back(std::shared_ptr<IOrderComponent>( new Product(it)));
    
    shared_ptr<OrderBox> mainBox ( new OrderBox());

    shared_ptr<OrderBox> box1 ( new OrderBox());
    shared_ptr<OrderBox> box2 ( new OrderBox());
    shared_ptr<OrderBox> box3 ( new OrderBox());
    shared_ptr<OrderBox> box4 ( new OrderBox());
    //constructing tree of OrderBox
    mainBox->add(products[0]);
    box4->add( products[5]);
    box3->add(products[4]);
    box3->add(products[3]);
    box2->add(box3);
    box2->add(products[2]);
    box1->add(products[1]);
    box1->add(box2);
    mainBox->add(box4);
    mainBox->add(box1);

    /*
                mainBox
                  /  /\  
                 /  /  \
                /  box4  box1
               /   /        /\
              /   product5 /  \
             /            /    \
        product0        box2    product1
                        /\
                       /  product2
                      /
                    box3
                    /\
                   /  \
            product3   product4
    */

    std::cout << "Total: " << mainBox->getPrice() << std::endl; 
    std::cout << "Verification: " << std::accumulate(prices.begin(), prices.end(),0) << std::endl;
    
    
    return 0;
}

