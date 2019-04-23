#include <iostream>

#include "tpbst.hpp"
 
int main() {
    TwoPhaseBST<int> tpbst;

    tpbst.print();
    //tpbst.insert("ceng213", "sec8", 26);
    tpbst.insert("ceng213", "sec5", 25);
    //tpbst.insert("ceng213", "sec14", 24);
    tpbst.insert("ceng213", "sec2", 23);
    tpbst.insert("ceng213", "sec3", 23);
    //tpbst.insert("ceng213", "sec6", 22);
    tpbst.insert("ceng213", "sec1", 22);
    tpbst.insert("ceng213", "sec0", 22);
    //tpbst.insert("ceng213", "sec10", 21);
    //tpbst.insert("ceng213", "sec9", 21);
    //tpbst.insert("ceng213", "sec10", 21);
    //tpbst.insert("ceng213", "sec2", 21);
    //tpbst.insert("ceng213", "sec5", 21);
    //tpbst.insert("ceng213", "sec7", 21);
    //tpbst.print();
    /*tpbst.insert("ceng477", "sec6", 50);
    tpbst.insert("ceng477", "sec3", 49);
    tpbst.insert("ceng477", "sec1", 50);
    tpbst.insert("ceng477", "sec2", 50);
    tpbst.insert("ceng477", "sec9", 50);
    tpbst.remove("ceng477", "sec3");
    tpbst.remove("ceng477", "sec6");*/
    //tpbst.insert();
    //tpbst.print();
    
    //tpbst.print("ceng210");
    //tpbst.print("ceng477");
    //tpbst.print("ceng");
    //std::cout << tpbst.find("ceng477","sec3");
    //tpbst.remove("ceng213", "sec6");
    //tpbst.remove("ceng213", "sec5");
    //tpbst.remove("ceng213", "sec7");
    tpbst.print();
    tpbst.remove("ceng213", "sec2");
    tpbst.remove("ceng213", "sec1");
    //tpbst.remove("ceng213", "sec1");
    //tpbst.remove("ceng213", "sec0");
    //tpbst.print();
    //tpbst.remove("ceng213", "sec8");
    //tpbst.remove("ceng213", "sec2");
    //tpbst.remove("ceng213", "sec14");
    //tpbst.remove("ceng213", "sec1");
    tpbst.print();
    //tpbst.print("ceng47", "sec1");
            /*.print("ceng213")
            .print("ceng213", "sec1")
            .insert("ceng213", "sec2", 26)
            .insert("ceng213", "sec1", 25)
            .insert("ceng213", "sec3", 24)
            .insert("ceng477", "sec2", 50)
            .insert("ceng477", "sec1", 49)
            .print()
            .print("ceng213")
            .print("ceng477")
            .print("ceng213", "sec1")
            .print("ceng477", "sec1")
            .remove("ceng213", "sec2")
            .remove("ceng477", "sec2")
            .print();*/

    //std::cout << "Number of enrolled students in ceng213 - sec3 is " << *(tpbst.find("ceng213", "sec3")) << std::endl;

    return 0;
}
