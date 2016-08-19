#pragma once

namespace SimplePaint
{
    enum FigureType { Rectangle, Ellipse };

    static QString figureName(const FigureType figureType)
    {
        switch (figureType)
        {
            case Rectangle:
                return "Rectangle";
            case Ellipse:
                return "Ellipse";
        }

        return "";
    }
}
