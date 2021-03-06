USE [atum2_db_1]
GO
/****** Object:  StoredProcedure [dbo].[atum_log_insert_server_map]    Script Date: 01/04/2017 11:46:40 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER OFF
GO

--!!!!
-- Name: atum_log_insert_server_map
-- Desc: inserts log
--====
--DROP PROCEDURE atum_log_insert_server_map
--GO
ALTER PROCEDURE [dbo].[atum_log_insert_server_map]
	@i_LogType						TINYINT,
	@i_MapIndex						SMALLINT,
	@i_ChannelIndex					SMALLINT,
	@i_ClientCount					INT,
	@i_MonsterCount					INT
--	@i_MGameServerID				INT
AS
	INSERT INTO atum_log_server_map
	VALUES (@i_LogType, GetDate(), @i_MapIndex, @i_ChannelIndex,
			@i_ClientCount, @i_MonsterCount, 0)

