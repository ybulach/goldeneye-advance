.TEXT
.SECTION .rodata
.ALIGN
.ARM

.ALIGN
.EXTERN AAS_lib_v111
.GLOBAL AAS_data_v111
AAS_data_v111:
.word AAS_lib_v111

.ALIGN
.GLOBAL AAS_DATA_NUM_MODS
AAS_DATA_NUM_MODS:
.short 0

.ALIGN
.GLOBAL AAS_ModSamples
AAS_ModSamples:

.ALIGN
.GLOBAL AAS_Sequence
AAS_Sequence:

.ALIGN
.GLOBAL AAS_NumChans
AAS_NumChans:
.byte

.ALIGN
.GLOBAL AAS_RestartPos
AAS_RestartPos:
.byte

.ALIGN
.GLOBAL AAS_SampleData
AAS_SampleData:
.byte 0

.ALIGN
.GLOBAL AAS_PatternData
AAS_PatternData:
.byte 0
