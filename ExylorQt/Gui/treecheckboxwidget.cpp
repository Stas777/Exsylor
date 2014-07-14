#include "treecheckboxwidget.h"

TreeCheckboxWidget::TreeCheckboxWidget(QWidget *parent) :
    QTreeView(parent)
{
    itemModel = new QStandardItemModel(this);
    usingPlainText = false;
}

void TreeCheckboxWidget::initWithCheckboxItems(Model *cur_model){
    usingPlainText = false;
    connect(itemModel, SIGNAL(itemChanged(QStandardItem *)),this, SLOT(actLikeACheckbox(QStandardItem*)));
    initAll(cur_model);
}

void TreeCheckboxWidget::initWithRadiobuttonItems(Model *cur_model, Data *cur_data){
    usingPlainText = false;
    initAll(cur_model);
    data = cur_data;
    connect(itemModel, SIGNAL(itemChanged(QStandardItem *)),this, SLOT(actLikeARadiobutton(QStandardItem*)));
    fillWithData();
}

void TreeCheckboxWidget::initWithPlainText(Model *cur_model){
    usingPlainText = true;
    initAll(cur_model);
}

void TreeCheckboxWidget::initAll(Model *cur_model){
    model = cur_model;
    initialDraw(model->getDataTemplate()->getAttributesVector());
    setModel(itemModel);
}

void TreeCheckboxWidget::initialDraw(const QVector<DataAttr> &vector) {
    itemModel->clear();
    rows.clear();
    itemModel = new QStandardItemModel();
    foreach (DataAttr item, vector) {
        QList<QStandardItem *> upRow = prepareRow(item.m_sTitle);
        itemModel->invisibleRootItem()->appendRow( upRow);
        foreach (QString name, item.m_ValNames) {
            QList<QStandardItem *> downRow = prepareCheckboxRow( name );
            upRow.first()->appendRow(downRow);
            rows += downRow;
        }
        rows += upRow;
    }
}

QList<QStandardItem*> TreeCheckboxWidget::prepareRow(const QString &name){
    QList<QStandardItem *> rowItems;
    QStandardItem *item = new QStandardItem(name);
    rowItems << item;
    return rowItems;
}


void TreeCheckboxWidget::fillWithData(){
    int count = 0;
    foreach (QStandardItem *item, rows) {
        if( item->isCheckable() ){
            item->setCheckState( data->getBit( count++ ) ? Qt::Checked : Qt::Unchecked );
        }
    }
}

QList<QStandardItem *> TreeCheckboxWidget::prepareCheckboxRow(const QString &name){
    QList<QStandardItem *> rowItems;
    QStandardItem *item = new QStandardItem(name);
    rowItems << item;
    if(!usingPlainText) item->setCheckable(true);
    return rowItems;
}


void TreeCheckboxWidget::actLikeACheckbox(QStandardItem *it){
    //updateData();
}


void TreeCheckboxWidget::actLikeARadiobutton(QStandardItem *it){
    //updateData();
    if(it->checkState() == Qt::Unchecked) return;
    foreach (QStandardItem * item, rows) {
        if(item->checkState() == Qt::Checked && item->parent() == it->parent() && it != item){
            item->setCheckState(Qt::Unchecked);
        }
    }
    data->setAttr(it->parent()->text(), it->text() );
    it->setCheckState(Qt::Checked);
}




TreeCheckboxWidget::~TreeCheckboxWidget()
{

}
