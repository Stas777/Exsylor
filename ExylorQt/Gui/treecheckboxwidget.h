#ifndef TREECHECKBOXWIDGET_H
#define TREECHECKBOXWIDGET_H
#include <QWidget>

#include <QTreeView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <../Kernel/Model.h>
class TreeCheckboxWidget : public QTreeView
{
    Q_OBJECT

public:
    explicit TreeCheckboxWidget(QWidget *parent = 0);
    ~TreeCheckboxWidget();
    void initWithCheckboxItems(Model *model);
    void initWithRadiobuttonItems(Model *model, Data *data);
    void initWithPlainText(Model *model);
private:

    bool usingPlainText;// radio or checkbox
    Model *model;
    Data *data;
    QStandardItemModel* itemModel;
    QList< QStandardItem * > rows;
    QList<QStandardItem *> prepareRow(const QString& name);
    QList<QStandardItem *> prepareCheckboxRow( const QString &name);
    void updateData();
    void initialDraw( const QVector<DataAttr> &) ;
    void initAll(Model *cur_model);
    void fillWithData();
private slots:


public slots:
    void actLikeACheckbox(QStandardItem *);
    void actLikeARadiobutton(QStandardItem *);


};

#endif // TREECHECKBOXWIDGET_H
