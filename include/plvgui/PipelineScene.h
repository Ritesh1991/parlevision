#ifndef PIPELINESCENE_H
#define PIPELINESCENE_H

#include <QGraphicsScene>
#include <QHash>

#include "RefPtr.h"
#include "Pipeline.h"
#include "PinConnection.h"


class QObject;

namespace plv
{
    class PipelineElement;
    class Pin;
    class PinConnection;
}

namespace plvgui
{
    class PipelineElementWidget;
    class PinWidget;
    class InteractiveLine;
    class ConnectionLine;

    /** A QGraphicsScene that wraps a Pipeline
      * to provide a graphical canvas for all the elements to live on.
      * This is only the model, it needs a QGraphicsView to render.
      */
    class PipelineScene : public QGraphicsScene
    {
        Q_OBJECT

    public:
        PipelineScene(plv::Pipeline* pipeline, QObject* parent);
        plv::RefPtr<plv::Pipeline> getPipeline() { return m_pipeline; }
        virtual bool event(QEvent * event);

    public slots:
        /** Add the given element to this scene
          * and to the underlying pipeline
          */
        void add(plv::PipelineElement* e);
        void add(plv::RefPtr<plv::PipelineElement> e);

        /** Add the given connection to this scene
          * and to the underlying pipeline
          */
        void add(plv::PinConnection* c);
        void add(plv::RefPtr<plv::PinConnection> c);

        /** Deletes the currently selected items (elements, connections etc.)
          * Has no effect if nothing is selected.
          */
        void deleteSelected();


        /** Remove the given element from this scene
          * and from the underlying pipeline
          */
        void remove(plv::PipelineElement* e);
        void remove(plv::RefPtr<plv::PipelineElement> e);

        /** Remove the given connection from this scene
          * and from the underlying pipeline
          */
        void remove(plv::PinConnection* c);
        void remove(plv::RefPtr<plv::PinConnection> c);

        /** Remove the given element from this scene
          * but not from the underlying pipeline
          */
        void handleRemove(plv::PipelineElement* e);
        void handleRemove(plv::RefPtr<plv::PipelineElement> e);

        /** Remove the given connection from this scene
          * but not from the underlying pipeline
          */
        void handleRemove(plv::PinConnection* c);
        void handleRemove(plv::RefPtr<plv::PinConnection> c);


    protected:
//        virtual void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
        virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);
        virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);
        virtual void dragEnterEvent ( QGraphicsSceneDragDropEvent * event );
        virtual void dragMoveEvent ( QGraphicsSceneDragDropEvent * event );
        virtual void dropEvent(QGraphicsSceneDragDropEvent *event);

    private:
        void clearLine();
        void handleConnectionCreation(PinWidget* source, PinWidget* target);

        plv::RefPtr<plv::Pipeline> m_pipeline;
        QHash<plv::PipelineElement*, PipelineElementWidget*> elementWidgets;
        QHash<plv::PinConnection*, ConnectionLine*> connectionLines;

        PipelineElementWidget* getWidgetFor(plv::PipelineElement* e) const;
        PinWidget* getWidgetFor(const plv::Pin* pw) const;
        ConnectionLine* getWidgetFor(plv::PinConnection* c) const;
        InteractiveLine* line;
    };

}

#endif // PIPELINESCENE_H
