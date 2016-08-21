#pragma once

namespace SimplePaint
{
    // figure creator abstract class
    // override create method to implement figure creation logic
    class AbstractFigureCreator
    {
    public:
        AbstractFigureCreator() {};
        virtual ~AbstractFigureCreator() {};

        // create a figure
        virtual QGraphicsItem* create(const QPointF& initialPos, QPen& pen) const = 0;
    };

    // concrete figure creator class
    template <class FigureClass>
    class FigureCreator : public AbstractFigureCreator
    {
    public:
        FigureCreator() {};
        ~FigureCreator() {};

    public:
        // create a figure at specified initial mouse position and pen
        QGraphicsItem* create(const QPointF& initialPos, QPen& pen) const override { return new FigureClass(initialPos, pen); }
    };

    // figures abstract factory
    class FigureFactory
    {
    public:
        FigureFactory() {};
        ~FigureFactory()
        {
            // free creators
            for (auto creator : _creators.values())
            {
                delete creator; creator = Q_NULLPTR;
            }
        }

        // register figure type
        template <class FigureClass> void add(const FigureType figureType)
        {
            _creators.insert(figureType, new FigureCreator<FigureClass>());
        }

        // create figure type object
        QGraphicsItem* create(const FigureType figureType, const QPointF& initialPos, QPen& pen) const
        {
            if (_creators.contains(figureType))
            {
                auto creator = _creators.value(figureType);
                if (creator)
                    return creator->create(initialPos, pen);
            }
            return Q_NULLPTR;
        }

    private:
        typedef QHash<FigureType, AbstractFigureCreator*> Creators;
        Creators _creators;
    };
}
