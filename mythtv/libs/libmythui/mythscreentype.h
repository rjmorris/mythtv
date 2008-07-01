#ifndef MYTHSCREEN_TYPE_H_
#define MYTHSCREEN_TYPE_H_

#include "mythuitype.h"
#include "qlist.h"

class MythScreenStack;

/**
 * Base Screen type
 */
class MythScreenType : public MythUIType
{
    Q_OBJECT

  public:
    MythScreenType(MythScreenStack *parent, const QString &name, 
                   bool fullscreen = true);
    virtual ~MythScreenType();

    virtual bool Create(void); // do the actual work of making the screen.
    virtual bool keyPressEvent(QKeyEvent *);

    // if the widget is full screen and obscures widgets below it
    bool IsFullscreen(void);
    void SetFullscreen(bool full);

    MythUIType *GetFocusWidget(void);
    bool SetFocusWidget(MythUIType *widget);
    virtual bool NextPrevWidgetFocus(bool up_or_down);
    bool BuildFocusList(void);

    MythScreenStack *GetScreenStack();

    virtual void aboutToHide(void);
    virtual void aboutToShow(void);

    bool IsDeleting(void);
    void SetDeleting(bool deleting);

  signals:
    void Exiting();

  protected:
    // for the global store..
    MythScreenType(MythUIType *parent, const QString &name, 
                   bool fullscreen = true);

    virtual void CopyFrom(MythUIType *base);
    virtual void CreateCopy(MythUIType *parent);
    virtual bool ParseElement(QDomElement &element);

    bool m_FullScreen;
    bool m_IsDeleting;

    MythUIType *m_CurrentFocusWidget;
    QList<MythUIType *> m_FocusWidgetList;

    MythScreenStack *m_ScreenStack;

    friend class XMLParseBase;
};

#endif
