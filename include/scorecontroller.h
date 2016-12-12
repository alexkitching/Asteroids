#ifndef _SCORECONTROLLER_H_
#define _SCORECONTROLLER_H_

class oScorecontroller
{
public:
	oScorecontroller();
	void DrawScore();
	void UpdateScore(int a_inewscore);
	friend class oObjectUpdateController;
private:
	int iCurrentScore = 0;
};

#endif // !_SCORECONTROLLER_H_
