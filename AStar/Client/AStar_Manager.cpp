#include "stdafx.h"
#include "AStar_Manager.h"
#include "GameObject_Manager.h"
#include "Terrain.h"
#include <vector>

IMPLEMENT_SINGLETON(CAStar_Manager)
CAStar_Manager::CAStar_Manager()
	:Mode(2)
{
}


CAStar_Manager::~CAStar_Manager()
{
}
void CAStar_Manager::Update()
{
	if (GetAsyncKeyState('1') & 0x8001)
	{
		Mode = 1;
	}
	if (GetAsyncKeyState('2') & 0x8001)
	{
		Mode = 2;
	}
	if (GetAsyncKeyState('3') & 0x8001)
	{
		Mode = 3;
	}
}
int CAStar_Manager::Get_TileIndex(const _vec3 & vPos)
{
	vector<TILE*>& vecTile = dynamic_cast<CTerrain*>(CGameObject_Manager::Get_Instance()->Get_Terrain())->Get_Tile();
	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		if (IsPicking(vPos, i))
			return i;
	}
	return -1;
}

bool CAStar_Manager::IsPicking(const _vec3 & vPos, const int & iIndex)
{

	vector<TILE*>& vecTile = dynamic_cast<CTerrain*>(CGameObject_Manager::Get_Instance()->Get_Terrain())->Get_Tile();

	_vec3 vPoint[4] =
	{
		{ vecTile[iIndex]->vPos.x, vecTile[iIndex]->vPos.y + (TILECY * 0.5f), 0.f },
		{ vecTile[iIndex]->vPos.x + (TILECX * 0.5f), vecTile[iIndex]->vPos.y , 0.f },
		{ vecTile[iIndex]->vPos.x, vecTile[iIndex]->vPos.y - (TILECY * 0.5f), 0.f },
		{ vecTile[iIndex]->vPos.x - (TILECX * 0.5f), vecTile[iIndex]->vPos.y , 0.f }
	};
	//2. 마름모꼴 방향벡터를 구하자!

	_vec3 vRhombusDir[4] =
	{
		vPoint[1] - vPoint[0],
		vPoint[2] - vPoint[1],
		vPoint[3] - vPoint[2],
		vPoint[0] - vPoint[3]
	};
	//3. 방향벡터의 법선벡터를 구하자! 
	_vec3 vRhombusNormal[4] =
	{
		{ -vRhombusDir[0].y, vRhombusDir[0].x, 0.f },
		{ -vRhombusDir[1].y, vRhombusDir[1].x, 0.f },
		{ -vRhombusDir[2].y, vRhombusDir[2].x, 0.f },
		{ -vRhombusDir[3].y, vRhombusDir[3].x, 0.f }
	};
	//4.마름모꼴 정점에서 마우스를 바라보는 방향벡터를 구해라!!! 
	_vec3 vMouseDir[4] =
	{
		vPos - vPoint[0],
		vPos - vPoint[1],
		vPos - vPoint[2],
		vPos - vPoint[3],

	};
	// 내가 구한 마우스를 바라보는 방향벡터와 마름모꼴의 법선벡터를 내적하자! 
	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3Normalize(&vMouseDir[i], &vMouseDir[i]);
		D3DXVec3Normalize(&vRhombusNormal[i], &vRhombusNormal[i]);

		if (0 < D3DXVec3Dot(&vRhombusNormal[i], &vMouseDir[i]))
			return false;
	}
	return true;
}

int32_t CAStar_Manager::HeuristicsCalc(const _vec3& lhs,const _vec3& rhs)
{
	if (Mode == 1)
	{
		 return std::abs(lhs.x - rhs.x) + std::abs(lhs.y - rhs.y);
	}
	else if (Mode == 2)
	{
		return max(std::abs(lhs.x - rhs.x), std::abs(lhs.y - rhs.y));
	}
	else if (Mode == 3)
	{
		return   std::sqrtf(((lhs.x - rhs.x) *  (lhs.x - rhs.x)) + ((lhs.y - rhs.y) *  (lhs.y - rhs.y))); 
	}
	
	return std::abs(lhs.x - rhs.x) + std::abs(lhs.y - rhs.y);
}

std::vector<_vec3>  CAStar_Manager::PathFinding(const int StartIdx, const int GoalIdx)
{
	vector<TILE*>& _Tiles = dynamic_cast<CTerrain*>(CGameObject_Manager::Get_Instance()->Get_Terrain())->Get_Tile();
	vector<list<TILE*>>& _Graphs =dynamic_cast<CTerrain*>(CGameObject_Manager::Get_Instance()->Get_Terrain())->Get_Graph();
	Start = StartIdx;
	Goal = GoalIdx;

	_Close.clear();
	_Open.clear();
	//   F    Index
	std::priority_queue<Cost, std::vector<Cost>, decltype(Comp)> _MinF{ Comp };
	// 최소 힙 : 기준 F, F가 같다면 H로 힙 구성

	const _vec3 GoalPos = _Tiles[GoalIdx]->vPos;
	const _vec3 StartPos = _Tiles[StartIdx]->vPos;

	Info _StartInfo;
	Cost _StartCost;

	_StartInfo.Parent = StartIdx;
	_StartInfo.G = 0;
	_StartInfo.H = HeuristicsCalc(GoalPos, StartPos);

	_StartCost.F = _StartInfo.G + _StartInfo.H;
	_StartCost.Index = StartIdx;

	_Open.insert({ StartIdx,std::move(_StartInfo) });
	_MinF.push(_StartCost);

	while (!_MinF.empty())
	{
		Cost _CurrentMinF= _MinF.top();
		_MinF.pop();

		if (_CurrentMinF.Index == GoalIdx)
		{
			int32_t CurrentIdx = GoalIdx;
			std::vector<_vec3> _Paths;
			_Close[GoalIdx] = _Open[GoalIdx].Parent;

			while (CurrentIdx!=StartIdx)
			{
				_Paths.emplace_back(_Tiles[CurrentIdx]->vPos);
				CurrentIdx = _Close[CurrentIdx];
			}

			return _Paths;
		}

		if (_Close.find(_CurrentMinF.Index) != std::end(_Close))
			continue;	

		const int32_t CurrentSelectIdx = _CurrentMinF.Index;
		const _vec3 CurrentSelectPos = _Tiles[CurrentSelectIdx]->vPos;
		const int32_t CurrentSelectParent = _Open[CurrentSelectIdx].Parent;
		const int32_t CurrentSelectG = _Open[CurrentSelectG].G;

		for (auto& Adj : _Graphs[CurrentSelectIdx])
		{
			Cost _AdjCost;

			const int32_t CurrentAdjIdx = Adj->iIndex; 
			const _vec3 CurrentAdjPos = _Tiles[CurrentAdjIdx]->vPos;

			auto IsOpenContainInfo = _Open.lower_bound(Adj->iIndex);
			if (IsOpenContainInfo == std::end(_Open) ||
				IsOpenContainInfo->first < Adj->iIndex)
			{
				Info _AdjInfo;
				_AdjInfo.Parent = CurrentSelectIdx;
				_AdjInfo.H = HeuristicsCalc(GoalPos, CurrentAdjPos);
				_AdjInfo.G = HeuristicsCalc(CurrentSelectPos, CurrentAdjPos);
				
				_AdjCost.F = _AdjInfo.H + _AdjInfo.G;
				_AdjCost.Index = CurrentAdjIdx;

				_Open.insert(IsOpenContainInfo,{ CurrentAdjIdx,std::move(_AdjInfo) });
				_MinF.push(std::move(_AdjCost));
			}
			else
			{
				int32_t GFromParent = CurrentSelectG + HeuristicsCalc(CurrentSelectPos, CurrentAdjPos);
				Info& _InfoAmend = IsOpenContainInfo->second;

				if (GFromParent < _InfoAmend.G)
				{
					_InfoAmend.G = GFromParent;
					_InfoAmend.Parent = CurrentSelectIdx;
					
					_AdjCost.F = _InfoAmend.G + _InfoAmend.H;
					_AdjCost.Index = CurrentAdjIdx;
				}
			}
		}
		_Open.erase(CurrentSelectIdx);
		_Close.insert({ CurrentSelectIdx ,CurrentSelectParent } );
	}


	//const _vec3 GoalPos = _Tiles[GoalIdx]->vPos;

	//// 시작 지점으로부터 검색된 사각형을 열린 목록에 추가한다.
	//Info _Info;
	//Cost _Cost;

	//_Info.G = 0;
	//_Cost.H =_Info.H = Calc(_Tiles[StartIdx]->vPos,GoalPos);
	//_Cost.F  =_Info.F = _Info.G + _Info.H;
	//_Cost.Index =_Info.Parent = StartIdx;
	// _Open.insert( { StartIdx, _Info } );
	// _CostQ.push(std::move(_Cost ) );

	//while (!_Open.empty() && !_CostQ.empty())
	//{
	//	// Close 에 없는 Cost 만 검사
	//	Cost CurrentCostMinInfo;

	//	while (!_CostQ.empty())
	//	{
	//		CurrentCostMinInfo = _CostQ.top();
	//		_CostQ.pop();

	//		if (_Close.find(CurrentCostMinInfo.Index) == std::end(_Close))
	//			break;
	//	}

	//	const Info& SelectInfo = _Open[CurrentCostMinInfo.Index];
	//	const int32_t SelectIdx = CurrentCostMinInfo.Index;
	//	const _vec3 SelectPos = _Tiles[SelectIdx]->vPos;

	//	if (GoalIdx == SelectIdx)
	//	{
	//		// 종료
	//		int32_t TargetIdx = GoalIdx;
	//		std::vector<_vec3> Paths;

	//		while (TargetIdx != StartIdx)
	//		{
	//			Paths.push_back(_Tiles[TargetIdx]->vPos); 
	//			// 부모의 인덱스 정보로 계속 갱신.
	//			TargetIdx = _Close[TargetIdx];
	//			//autoㅁ IsOpenFind = _Open.find(TargetIdx);
	//			//if (IsOpenFind != std::end(_Open))
	//			//{
	//			//	TargetIdx = IsOpenFind->second.Parent;               
	//			//}
	//			//else
	//			//{
	//			//	auto IsCloseFind = _Close.find(TargetIdx);

	//			//	if (IsCloseFind != std::end(_Close))
	//			//	{
	//			//		TargetIdx = IsCloseFind->second.Parent;
	//			//	}
	//			//}  
	//		} 
	//		return Paths;
	//	}
	//	// 닫힌 목록에 부모 정보를 저장.
	//	_Close[SelectIdx] = SelectInfo.Parent;
	//	_Open.erase(SelectIdx);

	//	for (auto& Adj : _Graphs[SelectIdx])
	//	{
	//		int32_t AdjIdx = Adj->iIndex;
	//		// 닫힌 목록에 있는 경우 무시 .
	//		auto IsFindIter =_Close.find(AdjIdx);
	//		if (IsFindIter != std::end(_Close))
	//			continue;

	//		// 만얀 이것이 열린 목록에 있지 않다면 이것을 오픈에 푸시하고 부모를 현재사각형으로
	//		// 만듭니다.
	//		auto AdjOpenIter = _Open.lower_bound(AdjIdx);
	//		if (AdjOpenIter == std::end(_Open) 
	//			|| 
	//			AdjOpenIter->first   < AdjIdx)
	//		{
	//			Info AdjInfo;
	//			const _vec3 AdjPos = _Tiles[AdjIdx]->vPos;  
	//			AdjInfo.Parent = SelectIdx;
	//			AdjInfo.G = SelectInfo.G+ Calc(SelectPos, AdjPos);
	//			AdjInfo.H = Calc(GoalPos, AdjPos);
	//			AdjInfo.F = AdjInfo.G + AdjInfo.H;

	//			Cost _AdjCost;
	//			_AdjCost.F = AdjInfo.F;
	//			_AdjCost.H = AdjInfo.H;
	//			_AdjCost.Index = AdjIdx;

	//			_Open.insert(AdjOpenIter,{ AdjIdx  ,std::move(AdjInfo )});

	//			// 인접 노드가 골이라면 비용을 0으로 만들어버리고
	//			// 클로즈에 바로 푸쉬 
	//			// 다음 루프에서 바로 경로로 이어버리기 위한 트릭
	//			if (AdjIdx == GoalIdx)
	//			{
	//				_AdjCost.H=_AdjCost.F = 0;
	//				_Close[AdjIdx] = SelectIdx;
	//			}
	//			_CostQ.push(_AdjCost);
	//		}
	//		// 이미 열린 목록에 있습니다.
	//		else
	//		{
	//			Info& _AdjInfo =AdjOpenIter->second;
	//			// 현재 타일에서 가는것이 더 유리한지 검사합니다. 
	//			float _ParentG = Calc(SelectPos, _Tiles[AdjIdx]->vPos);
	//			if ((SelectInfo.G+ _ParentG) < _AdjInfo.G)
	//			{
	//				_AdjInfo.G = SelectInfo.G + _ParentG;
	//				_AdjInfo.F = _AdjInfo.G + _AdjInfo.H;
	//				_AdjInfo.Parent = SelectIdx;

	//				Cost _Cost;
	//				_Cost.F = _AdjInfo.F;
	//				_Cost.H = _AdjInfo.H;
	//				_Cost.Index = AdjIdx;

	//				// 오픈목록이 갱신하면 최단거리 F 노드가 달라지므로 
	//				// 큐에 새로 푸시합니다.
	//				// 여기서 (노드의 중복이 발생하지만 OpenList 목록으로 루프를 컨트롤하니
	//				// 상관없다.)
	//				// 인접 노드가 골이라면 비용을 0으로 만들어버리고
	//			// 클로즈에 바로 푸쉬 
	//			// 다음 루프에서 바로 경로로 이어버리기 위한 트릭
	//				if (AdjIdx == GoalIdx)
	//				{
	//					_Cost.H = _Cost.F = 0;
	//					_Close[AdjIdx] = SelectIdx;
	//				}

	//				_CostQ.push(std::move(_Cost));
	//			}
	//		}
	//	};
	//}

	return std::vector<_vec3>{};
}

void CAStar_Manager::Make_Route(const int iStartIndex, const int iGoalIndex)
{
}

bool CAStar_Manager::Check_OpenList(const int iStartIndex, const int iGoalIndex)
{
	return false;
}

bool CAStar_Manager::Check_CloseList(const int iStartIndex, const int iGoalIndex)
{
	return false;
}

std::vector<_vec3>  CAStar_Manager::StartAStar(const _vec3 & vStart, const _vec3 & vGoal)
{
	const int32_t StartIdx = Get_TileIndex(vStart);
	const int32_t GoalIdx =Get_TileIndex(vGoal);

	if (StartIdx == -1 || GoalIdx == -1)
	{
		MessageBox(g_hWND, L"잘못된 위치선정", L"잘못된 위치선정", MB_OK);
		return std::vector<_vec3>{};
	}

	vector<TILE*>& _Tiles = dynamic_cast<CTerrain*>(CGameObject_Manager::Get_Instance()->Get_Terrain())->Get_Tile();
	if (_Tiles[GoalIdx]->byOption == 1)
	{
		MessageBox(g_hWND, L"갈수없는 벽", L"갈수없는 벽", MB_OK);
		return std::vector<_vec3>{};
	}

	return PathFinding(StartIdx, GoalIdx);
}
