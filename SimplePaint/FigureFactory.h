#pragma once

namespace SimplePaint
{
    class AbstractFigureCreator
    {
    public:
        AbstractFigureCreator() {};
        virtual ~AbstractFigureCreator() {};
        virtual QGraphicsItem* create(const QPointF& initialPos, QPen& pen) const = 0;
    };

    template <class FigureClass>
    class FigureCreator : public AbstractFigureCreator
    {
    public:
        FigureCreator() {};
        ~FigureCreator() {};

    public:
        QGraphicsItem* create(const QPointF& initialPos, QPen& pen) const override { return new FigureClass(initialPos, pen); }
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
