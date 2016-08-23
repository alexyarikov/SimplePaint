#include "stdafx.h"
#include "SimplePaintView.h"
#include "SimplePaintModel.h"

#ifdef TEST
#include "SimplePaintTest.h"
QTEST_MAIN(SimplePaintTest)
#else
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // application is easy and doesn't require separate abstraction layers of controller/presenter classes
    // to avoid over-engineering, there are Model (in fact model+controller) containing figures scene and implementing business logic
    // and View to show all that stuff
    SimplePaint::SimplePaintModel* model = new SimplePaint::SimplePaintModel(&app);
    SimplePaint::SimplePaintView view(*model);
    view.show();

    return app.exec();    
}
#endif
