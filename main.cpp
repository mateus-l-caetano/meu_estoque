#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "./use_case/cadastrodeitemusecase.h"
#include "./use_case/getestoqueusecase.h"
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

    QObject::connect(cadastroDeItemUseCase.get(), &CadastroDeItemUseCase::success, [](){
        qDebug() << "cadastro realizado com sucesso";
    });

    cadastroDeItemUseCase->execute(Item("nome", CATEGORIA1, 0.0, 10));

    getEstoqueUseCase->execute();

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
