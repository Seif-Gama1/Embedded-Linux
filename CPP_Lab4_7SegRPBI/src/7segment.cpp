#include "7segment.hpp"
#include <iostream>

/*
 * Common-cathode assumption:
 * 0 -> LOW  (segment ON)
 * 1 -> HIGH (segment OFF)
 */

 void SevenSeg::turnOffAll()
{
    a.setValue(0);
    b.setValue(0);
    c.setValue(0);
    d.setValue(0);
    e.setValue(0);
    f.setValue(0);
    g.setValue(0);
}


SevenSeg::SevenSeg()
    : a((512+14)), b((512+15)), c((512+18)), d((512+23)), e((512+24)), f((512+25)), g((512+8))
{
    // Configure all pins as outputs
    a.setDirection("out");
    b.setDirection("out");
    c.setDirection("out");
    d.setDirection("out");
    e.setDirection("out");
    f.setDirection("out");
    g.setDirection("out");

    turnOffAll();

    std::cout << "SevenSeg Constructor\n";
}

SevenSeg::~SevenSeg()
{
    std::cout << "SevenSeg Destructor\n";
}


void SevenSeg::writeDigit(int digit)
{
    if (digit < 0 || digit > 9) {
        std::cout << "SevenSeg: Invalid digit\n";
        return;
    }

    turnOffAll();

    switch (digit)
    {
        case 0:
            a.setValue(1); b.setValue(1); c.setValue(1);
            d.setValue(1); e.setValue(1); f.setValue(1);
            break;

        case 1:
            b.setValue(1); c.setValue(1);
            break;

        case 2:
            a.setValue(1); b.setValue(1); d.setValue(1);
            e.setValue(1); g.setValue(1);
            break;

        case 3:
            a.setValue(1); b.setValue(1); c.setValue(1);
            d.setValue(1); g.setValue(1);
            break;

        case 4:
            b.setValue(1); c.setValue(1);
            f.setValue(1); g.setValue(1);
            break;

        case 5:
            a.setValue(1); c.setValue(1); d.setValue(1);
            f.setValue(1); g.setValue(1);
            break;

        case 6:
            a.setValue(1); c.setValue(1); d.setValue(1);
            e.setValue(1); f.setValue(1); g.setValue(1);
            break;

        case 7:
            a.setValue(1); b.setValue(1); c.setValue(1);
            break;

        case 8:
            a.setValue(1); b.setValue(1); c.setValue(1);
            d.setValue(1); e.setValue(1); f.setValue(1); g.setValue(1);
            break;

        case 9:
            a.setValue(1); b.setValue(1); c.setValue(1);
            d.setValue(1); f.setValue(1); g.setValue(1);
            break;
    }
}
