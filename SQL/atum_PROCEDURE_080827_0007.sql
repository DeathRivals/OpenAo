USE [atum2_db_1]
GO
/****** Object:  StoredProcedure [dbo].[atum_PROCEDURE_080827_0007]    Script Date: 2017-01-02 14:53:04 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER OFF
GO

--------------------------------------------------------------------------------
-- PROCEDURE NAME	: dbo.atum_PROCEDURE_080827_0007
-- DESC				: -- // 2008-08-27 by cmkwon, Â³Â¯Ã„ÃµÂ¸Â®Â¸Â¦ ProcedureÂ·ÃŽ Â¼Ã¶ÃÂ¤ - 
--------------------------------------------------------------------------------
ALTER PROCEDURE [dbo].[atum_PROCEDURE_080827_0007]
AS
	SELECT wd.InfluenceType, wd.WartimeStage, wd.ContributionPoint, wd.InflLeaderCharacterUID, c.CharacterName, wd.InflSub1LeaderCharacterUID, c1.CharacterName, wd.InflSub2LeaderCharacterUID, c2.CharacterName
	FROM td_influencewardata wd  LEFT OUTER JOIN td_character c ON wd.InflLeaderCharacterUID = c.uniquenumber
		LEFT OUTER JOIN td_character c1	ON wd.InflSub1LeaderCharacterUID = c1.uniquenumber 
			LEFT OUTER JOIN td_character c2 ON wd.InflSub2LeaderCharacterUID = c2.uniquenumber;

