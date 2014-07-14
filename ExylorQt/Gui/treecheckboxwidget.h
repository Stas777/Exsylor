#ifndef TREECHECKBOXWIDGET_H
#define TREECHECKBOXWIDGET_H
#include <QWidget>

#include <QTreeView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <../../../../../some/Exsylor/ExylorQt/Kernel/Model.h>
class TreeCheckboxWidget : public QTreeView
{
    Q_OBJECT

public:
    explicit TreeCheckboxWidget(QTreeView *parent = 0);
    ~TreeCheckboxWidget();
    void initWithCheckboxItems(Model *model);
    void initWithRadiobuttonItems(Model *model);
    void initWithPlainText(Model *model);
private:

    bool usingPlainText;// radio or checkbox
    Model *model;
    QStandardItemModel* itemModel;
    QList< QStandardItem * > rows;
    QList<QStandardItem *> prepareRow(const QString& name);
    QList<QStandardItem *> prepareCheckboxRow( const QString &name);
    void updateData();
    void initialDraw( const QVector<DataAttr> &) ;
    void initAll(Model *cur_model);
private slots:


public slots:
    void actLikeACheckbox(QStandardItem *);
    void actLikeARadiobutton(QStandardItem *);


};

#endif // TREECHECKBOXWIDGET_H
