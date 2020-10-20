#pragma once
#include <queue>
#include <map>
#include <set>
#include <unordered_map>
#include <iterator>

struct Cost
{
	int32_t F = 0,Index = -1;
};

struct Info
{
	int32_t G = 0, H = 0, Parent = -1;
};

static auto Comp = [](const Cost& lhs ,const Cost& rhs) ->bool{
	return  lhs.F> rhs.F;
};

class CAStar_Manager
{
	DECLARE_SINGLETON(CAStar_Manager)
private:
	CAStar_Manager();
	~CAStar_Manager();
public:
	int32_t HeuristicsCalc(const _vec3& lhs, const _vec3& rhs);
	void Update();
	int Get_TileIndex(const _vec3& vPos);
	bool IsPicking(const _vec3& vPos, const int& iIndex);
	std::vector<_vec3>  PathFinding(const int iStartIndex, const int iGoalIndex);
	void Make_Route(const int iStartIndex, const int iGoalIndex);

	bool Check_OpenList(const int iStartIndex, const int iGoalIndex);
	bool Check_CloseList(const int iStartIndex, const int iGoalIndex);

public:
	std::vector<_vec3> StartAStar(const _vec3& vStart, const _vec3& vGoal);

	
	//      Self_Index        
	std::unordered_map<int32_t, Info> _Open;
	//      Self_Index         Parent Index
	std::unordered_map<int32_t, int32_t>  _Close;

	int Mode;
	int32_t Start = -1;
	int32_t Goal = -1;
private:
};

