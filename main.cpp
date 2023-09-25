#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "./use_case/cadastrodeitemusecase.h"
#include "./use_case/getestoqueusecase.h"
#include "./use_case/setitemvolumeusecase.h"
#include "./data/repository/estoquerepository.h"
#include "./data/database/database.h"
#include "./model/estoquemodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    DatabaseManager *database = DatabaseManager::getInstance();
    database->start();

    EstoqueRepository *estoqueRepository = new EstoqueRepository(database);

    std::unique_ptr<CadastroDeItemUseCase> cadastroDeItemUseCase(new CadastroDeItemUseCase(estoqueRepository));
    std::unique_ptr<GetEstoqueUseCase> getEstoqueUseCase(new GetEstoqueUseCase(estoqueRepository));
    std::unique_ptr<SetItemVolumeUseCase> setItemVolumeUseCase(new SetItemVolumeUseCase(estoqueRepository));

    std::unique_ptr<EstoqueModel> estoqueModel(new EstoqueModel(getEstoqueUseCase.get()));

    QQmlApplicationEngine engine;
    engine.setInitialProperties({{"estoqueModel", QVariant::fromValue(estoqueModel.get())}});

    const QUrl url(u"qrc:/meu_estoque/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
