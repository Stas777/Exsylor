#ifndef KNOWLEDGEDIALOGUE_H
#define KNOWLEDGEDIALOGUE_H

#include <QDialog>

namespace Ui {
class KnowledgeDialogue;
}

class KnowledgeDialogue : public QDialog
{
    Q_OBJECT

public:
    explicit KnowledgeDialogue(QWidget *parent = 0);
    ~KnowledgeDialogue();

private:
    Ui::KnowledgeDialogue *ui;
};

#endif // KNOWLEDGEDIALOGUE_H
