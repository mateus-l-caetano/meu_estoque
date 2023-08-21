#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "./use_case/cadastrodeitemusecase.h"
#include "./use_case/getestoqueusecase.h"
#include "./use_case/setitemvolumeusecase.h"
#include "./data/repository/estoquerepository.h"
#include "./data/database/database.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    DatabaseManager *database = DatabaseManager::getInstance();
    database->start();

    EstoqueRepository *estoqueRepository = new EstoqueRepository(database);

    std::unique_ptr<CadastroDeItemUseCase> cadastroDeItemUseCase(new CadastroDeItemUseCase(estoqueRepository));
    std::unique_ptr<GetEstoqueUseCase> getEstoqueUseCase(new GetEstoqueUseCase(estoqueRepository));
    std::unique_ptr<SetItemVolumeUseCase> setItemVolumeUseCase(new SetItemVolumeUseCase(estoqueRepository));

    QObject::connect(cadastroDeItemUseCase.get(), &CadastroDeItemUseCase::success, [](){
        qDebug() << "cadastro realizado com sucesso";
    });

    QObject::connect(setItemVolumeUseCase.get(), &SetItemVolumeUseCase::successInUpdatingItemVolume, [](){
        qDebug() << "atualizado com sucesso";
    });

//    cadastroDeItemUseCase->execute(Item("nome", CATEGORIA1, 0.0, 10));

    getEstoqueUseCase->execute();
    setItemVolumeUseCase->execute(25, "{53eda1fd-8de4-440b-9243-fb9f87f46e17}");

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/meu_estoque/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
