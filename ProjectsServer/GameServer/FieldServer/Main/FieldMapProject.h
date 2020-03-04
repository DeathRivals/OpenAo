// FieldMapProject.h: interface for the CFieldMapProject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIELDMAPPROJECT_H__A2E572D2_32EF_46A9_B701_F89F32D50966__INCLUDED_)
#define AFX_FIELDMAPPROJECT_H__A2E572D2_32EF_46A9_B701_F89F32D50966__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IOCP.h"
#include "MapProject.h"
#include "AtumProtocol.h"

#define MAX_MODULUS_NUMBER_TOTAL_NETWORK_STATE			10
#define MIN_MODULUS_NUMBER_TOTAL_NETWORK_STATE			3

typedef vector<SHOP_ITEM>	vectSHOP_ITEM;				// 2006-10-20 by cmkwon
class CShopInfo
{
public:
	// start 2011-10-28 by hskim, EP4 [Ʈ���� �ý���] - ũ����Ż �ý���
	CShopInfo()		{ m_OwnerCharacterUniqueNumber = 0; }
	virtual ~CShopInfo()	{ }
	// end 2011-10-28 by hskim, EP4 [Ʈ���� �ý���] - ũ����Ż �ý���

	SHOP_ITEM *GetSHOP_ITEMPtr(int i_itemNum);
	SHOP_ITEM *GetSHOP_ITEMPtrFrombuffer(int i_itemNum);	// 2010-01-26 by cmkwon, ĳ�� ������ �����Ǹ� �ý��� ���� - 

	void SetAllRemainCountForLimitedEdition(int iCount);	// 2011-10-28 by hskim, EP4 [Ʈ���� �ý���]
	void SetShopOwner(UID32_t OwnerCharacterUniqueNumber);	// 2011-10-28 by hskim, EP4 [Ʈ���� �ý���]
	UID32_t GetShopOwner();									// 2011-10-28 by hskim, EP4 [Ʈ���� �ý���]

// 2006-10-20 by cmkwon
//	map<UINT, SHOP_ITEM>	m_mapShopItem;			// ItemNum -> SHOP_ITEM
	vectSHOP_ITEM			m_vectShopItemList;		// 2006-10-20 by cmkwon
	GBUFFER					m_buffer;
	UID32_t					m_OwnerCharacterUniqueNumber;		// 2011-10-28 by hskim, EP4 [Ʈ���� �ý���]
};

typedef vector<WARP_TARGET_MAP_INFO_4_EXCHANGE>		 vectWARP_TARGET_MAP_INFO_4_EXCHANGE;		// 2007-01-29 by cmkwon

struct S_S1_CHARACTER_INFO		// 2007-08-30 by cmkwon, ȸ�Ƿ� �ý��� ���� - ����ü �߰�
{
	UID32_t			CharacterUID1;
	char			CharacterName1[SIZE_MAX_CHARACTER_NAME];
};
typedef mt_vector<S_S1_CHARACTER_INFO>			mtvectS_S1_CHARACTER_INFO;		// 2007-08-30 by cmkwon, ȸ�Ƿ� �ý��� ���� -

///////////////////////////////////////////////////////////////////////////////
/// \class		CFieldMapProject
///
/// \brief
/// \author		cmkwon
/// \version
/// \date		2004-03-26 ~ 2004-03-26
/// \warning
///////////////////////////////////////////////////////////////////////////////
class CFieldMapChannel;
class CFieldMonster;
class CCityWar;

class CODBCStatement;
class CFieldMapProject : public CMapProject
{
public:
	CFieldMapProject(CMapWorkspace * i_pMapWorkspace, PROJECTINFO * i_pProjectInfo);
	virtual ~CFieldMapProject();

	void SetNPCServerStartFlag(BOOL i_bStartFlag);
	BOOL GetNPCServerStartFlag(void);
	BOOL IsNPCServerMonsterCreated(void);		// 2011-10-28 by hskim, EP4 [Ʈ���� �ý���] - ũ����Ż �ý��� - NPC ������ ���Ͱ� ���� �Ǿ����� Ȯ��, ���� : �ʿ� ���Ͱ� ������ ������ FALSE

	BOOL LoadBUILDINGNPC(CODBCStatement *i_pOdbcStmt);			// ���� �ʿ� ���� �ǹ� �� ��� NPC�� ������ loading
	BOOL LoadShopInfo(CODBCStatement *i_pOdbcStmt);			// ���� �ʿ� ���� ������ �Ǹ� �������� �̸� loading
	BOOL LoadCityTargetWarpMap(CODBCStatement *i_pOdbcStmt);	// ���ÿ��� �����س��� �� �ִ� ���� ����Ʈ�� �̸� loading
	BOOL LoadWarpableUserList(CODBCStatement *i_pOdbcStmt);		// 2007-08-30 by cmkwon, ȸ�Ƿ� �ý��� ���� - �ε� �Լ� �߰�

	// ĳ���� �׾��� �� �����ϴ� default map�� ����
	BOOL SetDeadDefaultMap(void);
	CFieldMapProject* GetDeadDefaultMapProject(void);
	MapIndex_t GetDeadDefaultMapIndex(void);

	// Warp ����
	D3DXVECTOR3 GetDefaultPoint(void); // position vector�� �� �� �Ǿ��� �� Ȥ�� �׾��� ��, �⺻ ��ġ�� �˱� ����
	EVENTINFO* GetEventInfoByWarpIndex(int WarpIndex);
	D3DXVECTOR3 GetRandomWarpPoint(int EventAreaIndex);
	void GetRandomPositionInRadius(D3DXVECTOR3 *In, D3DXVECTOR3 *Out, float Radius);
	EVENTINFO *GetEventInfoByObjectTypeAndDistance(DWORD i_dwObjType, D3DXVECTOR3 *i_pVec3Position);
	OBJECTINFOSERVER *GetRandomObjectInfoServerPtrByEventIndex(short i_sEventIndex);
	EVENTINFO *GetEventInfoByMinimumDistance(EventType_t i_eventTy, D3DXVECTOR3 *i_pVec3Position);
	int GetRandomWarpTargetEventIndex(void);

	WARP_TARGET_MAP_INFO_4_EXCHANGE *GetWarpInfoByTargetMapIndex(MapIndex_t i_mapIdx);


	BOOL ResetAllChannel(void);
	BOOL FieldOnMonsterCreateW(MSG_FN_MONSTER_CREATE * i_pMonCreate);
	BOOL FieldOnMonsterDeleteW(MSG_FN_MONSTER_DELETE * i_pMonDelete);
	BOOL FieldOnMonsterMoveW(MSG_FN_MONSTER_MOVE * i_pMonMove);
	BOOL FieldOnGetCharacterInfoW(MSG_FN_GET_CHARACTER_INFO * i_pGetCInfo);
	BOOL FieldOnMissileMoveW(MSG_FN_MISSILE_MOVE * i_pMissileMove);
	BOOL FieldOnMonsterHPRecoveryW(MSG_FN_MONSTER_HPRECOVERY * i_pHPRecovery);
	BOOL FieldOnMonsterHideW(MSG_FN_MONSTER_HIDE * i_pMonHide);
	BOOL FieldOnMonsterShowW(MSG_FN_MONSTER_SHOW * i_pMonShow);
	BOOL FieldOnBattleAttackPrimaryW(MSG_FN_BATTLE_ATTACK_PRIMARY * i_pAttackPri);
	BOOL FieldOnBattleAttackSecondaryW(MSG_FN_BATTLE_ATTACK_SECONDARY * i_pAttackSec);
	BOOL FieldOnBattleAttackFindW(MSG_FN_BATTLE_ATTACK_FIND * i_pAttackFind);
	BOOL FieldOnMonsterChangeBodyconditionW(MSG_FN_MONSTER_CHANGE_BODYCONDITION * i_pChangeBody);
	BOOL FieldOnMonsterSkillUseSkillW(MSG_FN_MONSTER_SKILL_USE_SKILL * i_pUseSkill);
	BOOL FieldOnMonsterSkillEndSkillW(MSG_FN_MONSTER_SKILL_END_SKILL * i_pEndSkill);
	BOOL FieldOnMonsterAutoDestroyedW(MSG_FN_MONSTER_AUTO_DESTROYED * i_pAutoDestroyed);
	BOOL FieldOnMonsterChangeOkW(MSG_FN_MONSTER_CHANGE_OK * i_pMonChangeOk);		// 2011-05-11 by hskim, ���Ǵ�Ƽ 3�� - �ó׸� ���� ��� �߰� - �ش� ��ä�� Ư�� ���� ���� ��� �߰�

	CFieldMonster * GetFieldMonsterW(ChannelIndex_t i_channIdx, ClientIndex_t i_monsterIdx, int i_nTestIdx);

	// �̵� ���� ��ǥ���� üũ
	BOOL CheckCharacterPosition(D3DXVECTOR3 *pPosVector3, BOOL bFlagChangeableHeight);

	// ���� ����
	BOOL ChangeWeather(BitFlag16_t weather, BOOL bOnOff);

	// NPC ������ ����
	BOOL Send2NPCServer(BYTE *pData, int nSize);
	BOOL SendDelayBuffer2NPCFerver(void);

	// ���� �ʿ� �ִ� ĳ���͵� ��ο��� MSG ������
	// 2009-10-12 by cmkwon, ������ī ���� ��� ���� - SendMessageToAllInAllMapChannels, �����߰�(i_nStartCityMapIdx)
	void SendMessageToAllInAllMapChannels(BYTE *buffer, int size, BYTE i_byInfluenceMask=INFLUENCE_TYPE_ALL_MASK, MapIndex_t i_nStartCityMapIdx=VCN_CITY_MAP_INDEX);
	void SendSummonMessageToAllChannels(MSG_FN_ADMIN_SUMMON_MONSTER *i_pSummonMonster);

	CFieldMapChannel *GetFieldMapChannelByIndex(int i_nIndex, BOOL i_bOnlyEnabledChannel=FALSE);
	CFieldMapChannel *GetRandomFieldMapChannel(BOOL i_bOnlyEnabledChannel);
	CFieldMapChannel *GetFirstFieldMapChannel(BOOL i_bOnlyEnabledChannel);
// 2004-12-07 by cmkwon, ä�� �ǽð� ������ ���� �ʿ���� �Լ�
//	CFieldMapChannel *GetLastFieldMapChannel(BOOL i_bOnlyEnabledChannel);
	void MakeMsg_AllChannelState(int *o_pChannelCounts, MSG_FN_CONNECT_SET_CHANNEL_STATE *o_pChannelState);
	void OnDoMinutelyWorkFieldMapProject(void);
	void OnDoSecondlyWorkFieldMapProject(ATUM_DATE_TIME *pDateTime);
	BOOL IsMultiMapChannel(BYTE i_byCharInflTy);

	///////////////////////////////////////////////////////////////////////////
	// virtual
	// �ʱ�ȭ ����, 2004-03-26 by cmkwon
	virtual BOOL InitMapProject(void);

	// ä�� ����, added by kelovon, 20040324
	virtual BOOL InitializeMapChannels(int i_nChannel);
	virtual BOOL CleanMapChannels();
	virtual BOOL IncreaseMapChannels(int i_nChannelToAdd);

	void SetCityWarFieldMapProject(CCityWar *i_pCityWar);
	BYTE GetCityWarTeamTypeByGuildUID(UID32_t i_guildUID);
	BOOL IsCityWarStarted(void); 
// 2005-12-28 by cmkwon, ������� ����
//	BOOL IsCheckQuestForWarp(CFieldIOCPSocket *i_pFISock);

	///////////////////////////////////////////////////////////////////////////////
	// 2007-08-30 by cmkwon, ȸ�Ƿ� �ý��� ���� - CFieldMapProject�� ��� �Լ� �߰�
	S_S1_CHARACTER_INFO *FindInWarpableUserList(UID32_t i_charUID);
	BOOL FindInWarpableUserListByCharacterName(S_S1_CHARACTER_INFO *o_ps1CharInfo, char *i_szCharName);
	BOOL InsertWarpableUserList(UID32_t i_charUID, char *i_szCharName);
	BOOL PopInWarpableUserListByCharacterName(S_S1_CHARACTER_INFO *o_ps1CharInfo, char *i_szCharName);
	BOOL IsWarpableUser(UID32_t i_charUID, USHORT i_usRace);
	BOOL SendWarpableUserList(CFieldIOCPSocket *i_pFISoc);
	static INT GetConferenceRoomMapIndex(BYTE i_byCharInflTy);

	// start 2011-10-28 by hskim, EP4 [Ʈ���� �ý���] - ũ����Ż �ý���
	// �� ���� 1ȸ ����
	void SetEnterOneTimeLimited(BOOL bEnable);							// ��� ���� ����
	BOOL IsEnableEnterOneTimeLimited();									// ��� ���� Ȯ��
	void InsertEnterOneTimeLimited(UID32_t CharacterUID);				// ���� ĳ���� ����Ʈ �߰�
	BOOL IsEnterOneTimeLimited(UID32_t CharacterUID);					// ������ �������� �ִ��� Ȯ��
	BOOL IsGameStartNotAllowedUser(UID32_t CharacterUID);				// ���� ���۽� ������ ���� �������� Ȯ��
	void ResetEnterOneTimeLimited();									// ���� ��� ����

	// �Ҽ� ���ܸ� ����
	void SetEnterGuildLimited(BOOL bEnable, UID32_t GuildUID = 0);		// ��� ���� ����
	BOOL IsEnterGuildLimited(UID32_t GuildUID);							// ��� ���� Ȯ��

	// Ư�� ĳ���� ����
	void SetEnterCharacterLimited(BOOL bEnable, UID32_t CharacterUID = 0);	// ��� ���� ����
	BOOL IsEnterCharacterLimited(UID32_t CharacterUID);						// ��� ���� Ȯ��

	// �Ҽ� ���¸� ����
	void SetEnterInfluenceLimited(BOOL bEnable, BYTE InfluenceType = 0);	// ��� ���� ����
	BOOL IsEnterInfluenceLimited(BYTE InfluenceType);						// ��� ���� Ȯ��

	// �� �ִ� ���� �ο� 
	void SetEnterMaxiumUserLimited(BOOL bEnable);						// ��� ���� ����
	BOOL IsEnterMaxiumUserLimited();									// ��� ���� Ȯ��
	INT GetCurrentUser();												// ���� ���� ��ü ���� ����

	// �� ���� ���� Ȯ��
	BOOL IsEnterCondition(CFieldIOCPSocket *i_pFISoc);					// ���� ���� ȭ��

	Err_t IsEnableWarpByMapProject(CFieldIOCPSocket *i_pFISoc, BOOL bGameStart = FALSE);					// ���� �߰� �˻�
	// end 2011-10-28 by hskim, EP4 [Ʈ���� �ý���] - ũ����Ż �ý���

	// 2015-05-26 Future, Futures Shop Functions
	CShopInfo* GetShopInfoByBuildingNPC(UINT buildingIndex);
	CShopInfo* GetCashShopInfo();

public:
	CFieldMapProject			*m_pDeadDefaultMapProject;					// ĳ���� �׾��� �� �����ϴ� default map�� ����
	char						m_szUserFriendlyMapName[SIZE_MAX_MAP_NAME];	// ����ڰ� ���� �� �ִ� �� �̸�
	BitFlag16_t					m_Weather;									// ����, WEATHER_XXX

	ez_map<UINT, BUILDINGNPC*>	m_mapBuilding2Building;					// BuildingIndex -> BUILDINGNPC, �ǹ� �� ��� NPC�� ����, ����� memory ���� �ʿ�!
	ez_map<UINT, BUILDINGNPC*>	m_mapNPC2Building;						// NPCIndex -> BUILDINGNPC, �ǹ� �� ��� NPC�� ����, ����� memory ���� ���ʿ�!
	GBUFFER_SIZE_MAX_PACKET		m_buffGetBuildingListOK;				// Previously created message buffer for MSG_FC_CITY_GET_BUILDING_LIST_OK
	GBUFFER_SIZE_MAX_PACKET		m_buffGetWarpTargetMapListOK;			// Previously created message buffer for MSG_FC_CITY_GET_WARP_TARGET_MAP_LIST_OK

// 2007-01-29 by cmkwon, �Ʒ��� ���� ������
//	list<WARP_TARGET_MAP_INFO_4_EXCHANGE>	m_listCityWarpTargetMapInfo;	// ���ø��� ��� �����س��� �� �ִ� ���� ����
	vectWARP_TARGET_MAP_INFO_4_EXCHANGE		m_vectCityWarpInfoList;			// 2007-01-29 by cmkwon

	BOOL						m_bNPCServerStart;			// NPC Server �� �غ� �Ǿ������� �÷��׷� T_FN_MAPPROJECT_START_OK_ACK�� ���� �� TRUE�� �ȴ�.
	BOOL						m_bNPCServerMonsterCreated;	// 2011-10-28 by hskim, EP4 [Ʈ���� �ý���] - ũ����Ż �ý��� - NPC Server �� ���� ��ȯ �޽����� ������ �Ǵ��� Ȯ��.. �� ó�� ���� ���� ��Ŷ�� ������ TRUE ��
	CCityWar					*m_pRefCityWar2;

	int							m_nNextWarpTargetEventIndex;			// 2006-08-03 by cmkwon, 
	CFieldMapWorkspace			*m_pFieldMapWorkspace;

	///////////////////////////////////////////////////////////////////////////////
	// 2007-08-30 by cmkwon, ȸ�Ƿ� �ý��� ���� -
	mtvectS_S1_CHARACTER_INFO	m_mtvectWarpableUserList;		// 2007-08-30 by cmkwon, ȸ�Ƿ� �ý��� ���� - ��� ���� �߰�

	///////////////////////////////////////////////////////////////////////////////
	// 2010-01-26 by cmkwon, ĳ�� ������ �����Ǹ� �ý��� ���� - 
	BOOL LimitedEUpdate(UINT i_nBuildIdx, vectITEM_W_COUNT *i_pLimitedItemList);

	// start 2011-10-28 by hskim, EP4 [Ʈ���� �ý���] - ũ����Ż �ý���
public:
	BOOL						m_bEnableEnterOneTimeLimited;		// �� ���� 1ȸ ����
	mtvectCharacterUID			m_mtVectEnterOneTimeLimited;		// �� ���� 1ȸ ����

	BOOL						m_bEnableEnterGuildLimited;			// �� ���� ��� ����
	UID32_t						m_EnterGuildLimited;				// �� ���� ��� ����

	BOOL						m_bEnableEnterCharacterLimited;		// �� ���� ĳ�� ����
	UID32_t						m_EnterCharacterLimited;			// �� ���� ĳ�� ����

	BOOL						m_bEnableEnterInfluenceLimited;		// �� ���� ���� ����
	UID32_t						m_EnterInfluenceLimited;			// �� ���� ���� ����

	BOOL						m_bEnterMaxiumUserLimited;			// �� �ִ� ���� ���� ���� ���� ��� ����

	vectorMapEntranceCondition	m_EntranceCondition;				// �� ����� �ʿ��� �䱸 ���׵� (����� ������) - �ʱ⿡ ������ ����ȭ �ʿ� ����
	// end 2011-10-28 by hskim, EP4 [Ʈ���� �ý���] - ũ����Ż �ý���
public:
	map<UINT, CShopInfo*>		m_mapShopInfo;								// BuildingIndex -> CShopInfo
	CShopInfo* m_CashShopInfo;
};

#endif // !defined(AFX_FIELDMAPPROJECT_H__A2E572D2_32EF_46A9_B701_F89F32D50966__INCLUDED_)
