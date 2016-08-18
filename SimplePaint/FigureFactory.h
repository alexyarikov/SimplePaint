#pragma once

class BaseFigure;

class AbstractFigureCreator
{
public:
    AbstractFigureCreator() {};
    virtual ~AbstractFigureCreator() {};
    virtual BaseFigure* create(const QPen& pen) const = 0;
};

template <class FigureClass>
class FigureCreator : public AbstractFigureCreator
{
public:
    FigureCreator() {};
    ~FigureCreator() {};

public:
    BaseFigure* create(const QPen& pen) const override { return new FigureClass(pen); }
};

class FigureFactory
{
public:
    FigureFactory() {};
    ~FigureFactory()
    {
        for (auto creator : _creators.values())
            delete creator;
    }

    // figure types
    enum FigureType { Rectangle, Ellipse };

    // register figure type
    template <class FigureClass> void add(const FigureType figureType)
    {
        _creators.insert(figureType, new FigureCreator<FigureClass>());
    }

    // create figure type object
    BaseFigure* create(const FigureType figureType, const QPen& pen) const
    {
        if (_creators.contains(figureType))
        {
            auto creator = _creators.value(figureType);
            if (creator)
                return creator->create(pen);
        }
        return Q_NULLPTR;
    }

private:
    typedef QHash<FigureType, AbstractFigureCreator*> Creators;
    Creators _creators;
};
