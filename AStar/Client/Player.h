#pragma once
#include "GameObject.h"
class CPlayer final : public  CGameObject
{
private:
	explicit CPlayer();
public:
	virtual ~CPlayer();
public:
	void FrameMove(float fSpeed = 1.f); 
public :
	virtual HRESULT Ready_GameObject();
	virtual int		Update_GameObject();
	virtual void	Late_Update_GameObject();
	virtual void	Render_GameObject();
	virtual void	Release_GameObject();

private:
public :
	static CPlayer* Create(); 
	void Free(); 
	float MoveSpeed;
	_vec3 CurrentMoveTarget{float(640),float(360),0};
	std::vector<_vec3> Paths;
	void MoveAStar();
};

