{
	"patcher" : 	{
		"fileversion" : 1,
		"appversion" : 		{
			"major" : 8,
			"minor" : 0,
			"revision" : 8,
			"architecture" : "x64",
			"modernui" : 1
		}
,
		"classnamespace" : "box",
		"rect" : [ 126.0, 45.0, 1195.0, 705.0 ],
		"bglocked" : 0,
		"openinpresentation" : 0,
		"default_fontsize" : 12.0,
		"default_fontface" : 0,
		"default_fontname" : "Arial",
		"gridonopen" : 1,
		"gridsize" : [ 15.0, 15.0 ],
		"gridsnaponopen" : 1,
		"objectsnaponopen" : 1,
		"statusbarvisible" : 2,
		"toolbarvisible" : 1,
		"lefttoolbarpinned" : 0,
		"toptoolbarpinned" : 0,
		"righttoolbarpinned" : 0,
		"bottomtoolbarpinned" : 0,
		"toolbars_unpinned_last_save" : 15,
		"tallnewobj" : 0,
		"boxanimatetime" : 200,
		"enablehscroll" : 1,
		"enablevscroll" : 1,
		"devicewidth" : 0.0,
		"description" : "",
		"digest" : "",
		"tags" : "",
		"style" : "",
		"subpatcher_template" : "",
		"boxes" : [ 			{
				"box" : 				{
					"id" : "obj-48",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 0,
					"patching_rect" : [ 568.0, 432.0, 35.0, 22.0 ],
					"text" : "dac~"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-42",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 843.25, 386.5, 65.0, 20.0 ],
					"text" : "Presets"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.313974, 0.0, 0.048004, 1.0 ],
					"color" : [ 0.709562, 0.005658, 0.121731, 1.0 ],
					"id" : "obj-49",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 328.5, 512.5, 53.0, 22.0 ],
					"text" : "cycle~ 2"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-36",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 265.5, 483.5, 43.0, 20.0 ],
					"text" : "Ø"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.65908, 0.0065, 0.107064, 1.0 ],
					"format" : 6,
					"id" : "obj-39",
					"maxclass" : "flonum",
					"maximum" : 1.0,
					"minimum" : 0.0,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 213.5, 481.5, 50.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-40",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 234.5, 512.5, 43.0, 20.0 ],
					"text" : "VCO2"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-41",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 234.5, 571.0, 82.0, 20.0 ],
					"text" : "Tropical VCA"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.313974, 0.0, 0.048004, 1.0 ],
					"color" : [ 0.709562, 0.005658, 0.121731, 1.0 ],
					"id" : "obj-43",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 132.5, 569.0, 100.0, 22.0 ],
					"text" : "+~"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.52549, 0.062745, 0.003922, 1.0 ],
					"format" : 6,
					"id" : "obj-46",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 132.5, 481.5, 50.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.313974, 0.0, 0.048004, 1.0 ],
					"color" : [ 0.709562, 0.005658, 0.121731, 1.0 ],
					"id" : "obj-47",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 132.5, 510.5, 100.0, 22.0 ],
					"text" : "cycle~"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-31",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 129.0, 447.0, 415.0, 20.0 ],
					"text" : "NB i VCA tropicali sono interessanti anche modulati in bassa frequenenza"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-14",
					"maxclass" : "preset",
					"numinlets" : 1,
					"numoutlets" : 4,
					"outlettype" : [ "preset", "int", "preset", "int" ],
					"patching_rect" : [ 910.25, 386.5, 164.0, 17.0 ],
					"preset_data" : [ 						{
							"number" : 1,
							"data" : [ 5, "obj-3", "flonum", "float", 218.0, 5, "obj-6", "flonum", "float", -1.0, 5, "obj-10", "flonum", "float", 0.0, 5, "obj-8", "flonum", "float", 1.0, 5, "obj-15", "flonum", "float", 1.0, 6, "obj-32", "gain~", "list", 100, 10.0, 5, "obj-5", "flonum", "float", 0.0, 5, "obj-2", "flonum", "float", 0.0, 5, "obj-72", "flonum", "float", 0.0, 5, "obj-75", "flonum", "float", 2.0, 5, "obj-87", "flonum", "float", 0.0, 5, "obj-85", "flonum", "float", 1.0, 5, "obj-81", "flonum", "float", 0.0, 5, "obj-78", "flonum", "float", 0.0, 5, "obj-76", "flonum", "float", 3.0, 5, "obj-100", "flonum", "float", 0.0, 5, "obj-98", "flonum", "float", 1.0, 5, "obj-94", "flonum", "float", 0.0, 5, "obj-91", "flonum", "float", 0.0, 5, "obj-89", "flonum", "float", 4.0, 5, "obj-113", "flonum", "float", 0.0, 5, "obj-111", "flonum", "float", 1.0, 5, "obj-107", "flonum", "float", 0.0, 5, "obj-104", "flonum", "float", 0.0, 5, "obj-102", "flonum", "float", 5.0 ]
						}
, 						{
							"number" : 2,
							"data" : [ 5, "obj-3", "flonum", "float", 218.0, 5, "obj-6", "flonum", "float", -1.0, 5, "obj-10", "flonum", "float", 436.0, 5, "obj-8", "flonum", "float", -0.490000009536743, 5, "obj-15", "flonum", "float", 1.0, 6, "obj-32", "gain~", "list", 100, 10.0, 5, "obj-5", "flonum", "float", 0.0, 5, "obj-2", "flonum", "float", 0.0, 5, "obj-72", "flonum", "float", 0.0, 5, "obj-75", "flonum", "float", 2.0, 5, "obj-87", "flonum", "float", 654.0, 5, "obj-85", "flonum", "float", 1.0, 5, "obj-81", "flonum", "float", 0.0, 5, "obj-78", "flonum", "float", 0.0, 5, "obj-76", "flonum", "float", 3.0, 5, "obj-100", "flonum", "float", 872.0, 5, "obj-98", "flonum", "float", 1.0, 5, "obj-94", "flonum", "float", 0.0, 5, "obj-91", "flonum", "float", 0.0, 5, "obj-89", "flonum", "float", 4.0, 5, "obj-113", "flonum", "float", 1090.0, 5, "obj-111", "flonum", "float", 1.0, 5, "obj-107", "flonum", "float", 0.0, 5, "obj-104", "flonum", "float", 0.0, 5, "obj-102", "flonum", "float", 5.0 ]
						}
, 						{
							"number" : 3,
							"data" : [ 5, "obj-3", "flonum", "float", 218.0, 5, "obj-6", "flonum", "float", -1.0, 5, "obj-10", "flonum", "float", 436.82000732421875, 5, "obj-8", "flonum", "float", -0.490000009536743, 5, "obj-15", "flonum", "float", 1.0, 6, "obj-32", "gain~", "list", 100, 10.0, 5, "obj-5", "flonum", "float", 0.0, 5, "obj-2", "flonum", "float", 0.0, 5, "obj-72", "flonum", "float", 0.409999996423721, 5, "obj-75", "flonum", "float", 2.0, 5, "obj-87", "flonum", "float", 654.0, 5, "obj-85", "flonum", "float", 1.0, 5, "obj-81", "flonum", "float", 0.0, 5, "obj-78", "flonum", "float", 0.0, 5, "obj-76", "flonum", "float", 3.0, 5, "obj-100", "flonum", "float", 872.0, 5, "obj-98", "flonum", "float", 1.0, 5, "obj-94", "flonum", "float", 0.0, 5, "obj-91", "flonum", "float", 0.0, 5, "obj-89", "flonum", "float", 4.0, 5, "obj-113", "flonum", "float", 1090.0, 5, "obj-111", "flonum", "float", 1.0, 5, "obj-107", "flonum", "float", 0.0, 5, "obj-104", "flonum", "float", 0.0, 5, "obj-102", "flonum", "float", 5.0 ]
						}
, 						{
							"number" : 4,
							"data" : [ 5, "obj-3", "flonum", "float", 41.0, 5, "obj-6", "flonum", "float", -1.0, 5, "obj-10", "flonum", "float", 82.819999694824219, 5, "obj-8", "flonum", "float", -0.490000009536743, 5, "obj-15", "flonum", "float", 1.0, 6, "obj-32", "gain~", "list", 100, 10.0, 5, "obj-5", "flonum", "float", 0.0, 5, "obj-2", "flonum", "float", 0.0, 5, "obj-72", "flonum", "float", 0.409999996423721, 5, "obj-75", "flonum", "float", 2.0, 5, "obj-87", "flonum", "float", 123.0, 5, "obj-85", "flonum", "float", 1.0, 5, "obj-81", "flonum", "float", 0.0, 5, "obj-78", "flonum", "float", 0.0, 5, "obj-76", "flonum", "float", 3.0, 5, "obj-100", "flonum", "float", 167.160003662109375, 5, "obj-98", "flonum", "float", -0.560000002384186, 5, "obj-94", "flonum", "float", 0.0, 5, "obj-91", "flonum", "float", 0.790000021457672, 5, "obj-89", "flonum", "float", 4.0, 5, "obj-113", "flonum", "float", 205.0, 5, "obj-111", "flonum", "float", 1.0, 5, "obj-107", "flonum", "float", 0.0, 5, "obj-104", "flonum", "float", 0.0, 5, "obj-102", "flonum", "float", 5.0 ]
						}
, 						{
							"number" : 5,
							"data" : [ 5, "obj-3", "flonum", "float", 48.0, 5, "obj-6", "flonum", "float", -1.0, 5, "obj-10", "flonum", "float", 96.819999694824219, 5, "obj-8", "flonum", "float", -0.490000009536743, 5, "obj-15", "flonum", "float", 1.0, 6, "obj-32", "gain~", "list", 100, 10.0, 5, "obj-5", "flonum", "float", 0.0, 5, "obj-2", "flonum", "float", 0.0, 5, "obj-72", "flonum", "float", 0.409999996423721, 5, "obj-75", "flonum", "float", 2.0, 5, "obj-87", "flonum", "float", 144.0, 5, "obj-85", "flonum", "float", 1.0, 5, "obj-81", "flonum", "float", 0.0, 5, "obj-78", "flonum", "float", 0.0, 5, "obj-76", "flonum", "float", 3.0, 5, "obj-100", "flonum", "float", 195.160003662109375, 5, "obj-98", "flonum", "float", -0.560000002384186, 5, "obj-94", "flonum", "float", 0.0, 5, "obj-91", "flonum", "float", 0.790000021457672, 5, "obj-89", "flonum", "float", 4.0, 5, "obj-113", "flonum", "float", 240.0, 5, "obj-111", "flonum", "float", -0.509999990463257, 5, "obj-107", "flonum", "float", 0.0, 5, "obj-104", "flonum", "float", 0.0, 5, "obj-102", "flonum", "float", 5.0, 5, "obj-46", "flonum", "float", 0.0, 5, "obj-39", "flonum", "float", 0.0 ]
						}
, 						{
							"number" : 6,
							"data" : [ 5, "obj-3", "flonum", "float", 55.0, 5, "obj-6", "flonum", "float", -1.0, 5, "obj-10", "flonum", "float", 110.0, 5, "obj-8", "flonum", "float", -1.0, 5, "obj-15", "flonum", "float", 1.0, 6, "obj-32", "gain~", "list", 100, 10.0, 5, "obj-5", "flonum", "float", 0.0, 5, "obj-2", "flonum", "float", 0.0, 5, "obj-72", "flonum", "float", 0.0, 5, "obj-75", "flonum", "float", 2.0, 5, "obj-87", "flonum", "float", 165.0, 5, "obj-85", "flonum", "float", 1.0, 5, "obj-81", "flonum", "float", 0.0, 5, "obj-78", "flonum", "float", 0.0, 5, "obj-76", "flonum", "float", 3.0, 5, "obj-100", "flonum", "float", 220.0, 5, "obj-98", "flonum", "float", -0.853999972343445, 5, "obj-94", "flonum", "float", 0.0, 5, "obj-91", "flonum", "float", 0.0, 5, "obj-89", "flonum", "float", 4.0, 5, "obj-113", "flonum", "float", 550.90997314453125, 5, "obj-111", "flonum", "float", -0.800000011920929, 5, "obj-107", "flonum", "float", 0.0, 5, "obj-104", "flonum", "float", 0.090999998152256, 5, "obj-102", "flonum", "float", 10.0 ]
						}
, 						{
							"number" : 7,
							"data" : [ 5, "obj-3", "flonum", "float", 70.0, 5, "obj-6", "flonum", "float", -1.0, 5, "obj-10", "flonum", "float", 141.479995727539062, 5, "obj-8", "flonum", "float", -1.0, 5, "obj-15", "flonum", "float", 1.0, 6, "obj-32", "gain~", "list", 100, 10.0, 5, "obj-5", "flonum", "float", 0.0, 5, "obj-2", "flonum", "float", 0.0, 5, "obj-72", "flonum", "float", 0.740000009536743, 5, "obj-75", "flonum", "float", 0.5, 5, "obj-87", "flonum", "float", 210.0, 5, "obj-85", "flonum", "float", 0.0, 5, "obj-81", "flonum", "float", 0.0, 5, "obj-78", "flonum", "float", 0.0, 5, "obj-76", "flonum", "float", 3.0, 5, "obj-100", "flonum", "float", 280.160003662109375, 5, "obj-98", "flonum", "float", -1.0, 5, "obj-94", "flonum", "float", 0.0, 5, "obj-91", "flonum", "float", 0.03999999910593, 5, "obj-89", "flonum", "float", 8.0, 5, "obj-113", "flonum", "float", 700.0, 5, "obj-111", "flonum", "float", 0.0, 5, "obj-107", "flonum", "float", 0.0, 5, "obj-104", "flonum", "float", 0.0, 5, "obj-102", "flonum", "float", 10.0, 5, "obj-46", "flonum", "float", 0.0, 5, "obj-39", "flonum", "float", 0.0 ]
						}
, 						{
							"number" : 8,
							"data" : [ 5, "obj-3", "flonum", "float", 70.0, 5, "obj-6", "flonum", "float", -1.0, 5, "obj-10", "flonum", "float", 140.537994384765625, 5, "obj-8", "flonum", "float", -1.0, 5, "obj-15", "flonum", "float", 1.0, 6, "obj-32", "gain~", "list", 100, 10.0, 5, "obj-5", "flonum", "float", 0.0, 5, "obj-2", "flonum", "float", 0.0, 5, "obj-72", "flonum", "float", 0.268999993801117, 5, "obj-75", "flonum", "float", 2.0, 5, "obj-87", "flonum", "float", 210.0, 5, "obj-85", "flonum", "float", 1.0, 5, "obj-81", "flonum", "float", 0.0, 5, "obj-78", "flonum", "float", 0.0, 5, "obj-76", "flonum", "float", 3.0, 5, "obj-100", "flonum", "float", 280.0, 5, "obj-98", "flonum", "float", 1.0, 5, "obj-94", "flonum", "float", 0.0, 5, "obj-91", "flonum", "float", 0.0, 5, "obj-89", "flonum", "float", 4.0, 5, "obj-113", "flonum", "float", 1411.800048828125, 5, "obj-111", "flonum", "float", 0.109999999403954, 5, "obj-107", "flonum", "float", 0.0, 5, "obj-104", "flonum", "float", 0.589999973773956, 5, "obj-102", "flonum", "float", 20.0, 5, "obj-46", "flonum", "float", 0.0, 5, "obj-39", "flonum", "float", 0.0 ]
						}
, 						{
							"number" : 9,
							"data" : [ 5, "obj-3", "flonum", "float", 70.0, 5, "obj-6", "flonum", "float", 1.0, 5, "obj-10", "flonum", "float", 140.0, 5, "obj-8", "flonum", "float", 1.0, 5, "obj-15", "flonum", "float", 1.0, 6, "obj-32", "gain~", "list", 100, 10.0, 5, "obj-5", "flonum", "float", 0.0, 5, "obj-2", "flonum", "float", 0.0, 5, "obj-72", "flonum", "float", 0.0, 5, "obj-75", "flonum", "float", 2.0, 5, "obj-87", "flonum", "float", 210.0, 5, "obj-85", "flonum", "float", -1.0, 5, "obj-81", "flonum", "float", 0.0, 5, "obj-78", "flonum", "float", 0.0, 5, "obj-76", "flonum", "float", 3.0, 5, "obj-100", "flonum", "float", 560.0, 5, "obj-98", "flonum", "float", -1.0, 5, "obj-94", "flonum", "float", 0.0, 5, "obj-91", "flonum", "float", 0.0, 5, "obj-89", "flonum", "float", 4.0, 5, "obj-113", "flonum", "float", 1400.0, 5, "obj-111", "flonum", "float", 1.0, 5, "obj-107", "flonum", "float", 0.0, 5, "obj-104", "flonum", "float", 0.0, 5, "obj-102", "flonum", "float", 5.0, 5, "obj-46", "flonum", "float", 0.0, 5, "obj-39", "flonum", "float", 0.0 ]
						}
, 						{
							"number" : 10,
							"data" : [ 5, "obj-3", "flonum", "float", 70.0, 5, "obj-6", "flonum", "float", 1.0, 5, "obj-10", "flonum", "float", 140.0, 5, "obj-8", "flonum", "float", 1.0, 5, "obj-15", "flonum", "float", 1.0, 6, "obj-32", "gain~", "list", 100, 10.0, 5, "obj-5", "flonum", "float", 0.0, 5, "obj-2", "flonum", "float", 0.0, 5, "obj-72", "flonum", "float", 0.0, 5, "obj-75", "flonum", "float", 2.0, 5, "obj-87", "flonum", "float", 210.0, 5, "obj-85", "flonum", "float", -1.0, 5, "obj-81", "flonum", "float", 0.0, 5, "obj-78", "flonum", "float", 0.0, 5, "obj-76", "flonum", "float", 3.0, 5, "obj-100", "flonum", "float", 280.0, 5, "obj-98", "flonum", "float", 1.0, 5, "obj-94", "flonum", "float", 0.0, 5, "obj-91", "flonum", "float", 0.0, 5, "obj-89", "flonum", "float", 4.0, 5, "obj-113", "flonum", "float", 700.0, 5, "obj-111", "flonum", "float", -1.0, 5, "obj-107", "flonum", "float", 0.0, 5, "obj-104", "flonum", "float", 0.0, 5, "obj-102", "flonum", "float", 5.0, 5, "obj-46", "flonum", "float", 0.0, 5, "obj-39", "flonum", "float", 0.0 ]
						}
, 						{
							"number" : 11,
							"data" : [ 5, "obj-3", "flonum", "float", 70.0, 5, "obj-6", "flonum", "float", 1.0, 5, "obj-10", "flonum", "float", 140.0, 5, "obj-8", "flonum", "float", 1.0, 5, "obj-15", "flonum", "float", 1.0, 6, "obj-32", "gain~", "list", 100, 10.0, 5, "obj-5", "flonum", "float", 0.0, 5, "obj-2", "flonum", "float", 0.0, 5, "obj-72", "flonum", "float", 0.0, 5, "obj-75", "flonum", "float", 2.0, 5, "obj-87", "flonum", "float", 210.0, 5, "obj-85", "flonum", "float", 1.0, 5, "obj-81", "flonum", "float", 0.0, 5, "obj-78", "flonum", "float", 0.0, 5, "obj-76", "flonum", "float", 3.0, 5, "obj-100", "flonum", "float", 280.0, 5, "obj-98", "flonum", "float", -1.0, 5, "obj-94", "flonum", "float", 0.0, 5, "obj-91", "flonum", "float", 0.0, 5, "obj-89", "flonum", "float", 4.0, 5, "obj-113", "flonum", "float", 700.0, 5, "obj-111", "flonum", "float", 1.0, 5, "obj-107", "flonum", "float", 0.0, 5, "obj-104", "flonum", "float", 0.0, 5, "obj-102", "flonum", "float", 5.0, 5, "obj-46", "flonum", "float", 0.0, 5, "obj-39", "flonum", "float", 0.0 ]
						}
, 						{
							"number" : 12,
							"data" : [ 5, "obj-3", "flonum", "float", 70.010002136230469, 5, "obj-6", "flonum", "float", -1.0, 5, "obj-10", "flonum", "float", 140.020004272460938, 5, "obj-8", "flonum", "float", 1.0, 5, "obj-15", "flonum", "float", 1.0, 6, "obj-32", "gain~", "list", 100, 10.0, 5, "obj-5", "flonum", "float", 0.0, 5, "obj-2", "flonum", "float", 0.0, 5, "obj-72", "flonum", "float", 0.0, 5, "obj-75", "flonum", "float", 2.0, 5, "obj-87", "flonum", "float", 210.029998779296875, 5, "obj-85", "flonum", "float", 0.0, 5, "obj-81", "flonum", "float", 0.0, 5, "obj-78", "flonum", "float", 0.0, 5, "obj-76", "flonum", "float", 3.0, 5, "obj-100", "flonum", "float", 560.08001708984375, 5, "obj-98", "flonum", "float", 0.045000001788139, 5, "obj-94", "flonum", "float", 0.0, 5, "obj-91", "flonum", "float", 0.0, 5, "obj-89", "flonum", "float", 8.0, 5, "obj-113", "flonum", "float", 704.70001220703125, 5, "obj-111", "flonum", "float", -0.409999996423721, 5, "obj-107", "flonum", "float", 0.0, 5, "obj-104", "flonum", "float", 0.46000000834465, 5, "obj-102", "flonum", "float", 10.0, 5, "obj-46", "flonum", "float", 0.0, 5, "obj-39", "flonum", "float", 0.0 ]
						}
, 						{
							"number" : 13,
							"data" : [ 5, "obj-3", "flonum", "float", 41.0, 5, "obj-6", "flonum", "float", -1.0, 5, "obj-10", "flonum", "float", 82.0, 5, "obj-8", "flonum", "float", -1.0, 5, "obj-15", "flonum", "float", 1.0, 6, "obj-32", "gain~", "list", 100, 10.0, 5, "obj-5", "flonum", "float", 0.0, 5, "obj-2", "flonum", "float", 0.0, 5, "obj-72", "flonum", "float", 0.0, 5, "obj-75", "flonum", "float", 2.0, 5, "obj-87", "flonum", "float", 123.0, 5, "obj-85", "flonum", "float", 1.0, 5, "obj-81", "flonum", "float", 0.0, 5, "obj-78", "flonum", "float", 0.0, 5, "obj-76", "flonum", "float", 3.0, 5, "obj-100", "flonum", "float", 328.0, 5, "obj-98", "flonum", "float", 1.0, 5, "obj-94", "flonum", "float", 0.0, 5, "obj-91", "flonum", "float", 0.0, 5, "obj-89", "flonum", "float", 8.0, 5, "obj-113", "flonum", "float", 49241.51953125, 5, "obj-111", "flonum", "float", -0.25900000333786, 5, "obj-107", "flonum", "float", 0.0, 5, "obj-104", "flonum", "float", 0.310000002384186, 5, "obj-102", "flonum", "float", 1192.0, 5, "obj-46", "flonum", "float", 0.0, 5, "obj-39", "flonum", "float", 0.0 ]
						}
 ]
				}

			}
, 			{
				"box" : 				{
					"hidden" : 1,
					"id" : "obj-131",
					"maxclass" : "button",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 777.5, 155.5, 24.0, 24.0 ]
				}

			}
, 			{
				"box" : 				{
					"hidden" : 1,
					"id" : "obj-130",
					"maxclass" : "button",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 587.0, 151.5, 24.0, 24.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-128",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 310.5, 153.5, 61.0, 20.0 ],
					"text" : "Multiplier"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-127",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 502.5, 151.5, 65.0, 20.0 ],
					"text" : "Multiplier"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-126",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 693.5, 153.5, 63.0, 20.0 ],
					"text" : "Multiplier"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-125",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 803.5, 70.0, 134.0, 20.0 ],
					"text" : "Calculate 5th harmonic"
				}

			}
, 			{
				"box" : 				{
					"hidden" : 1,
					"id" : "obj-124",
					"maxclass" : "button",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 198.5, 149.5, 24.0, 24.0 ]
				}

			}
, 			{
				"box" : 				{
					"hidden" : 1,
					"id" : "obj-122",
					"maxclass" : "button",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 378.5, 153.5, 24.0, 24.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-118",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 890.75, 155.5, 103.0, 20.0 ],
					"text" : "Multiplier"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.313974, 0.0, 0.048004, 1.0 ],
					"color" : [ 0.709562, 0.005658, 0.121731, 1.0 ],
					"id" : "obj-117",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 681.0, 337.5, 100.0, 22.0 ],
					"text" : "minimum~"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.313974, 0.0, 0.048004, 1.0 ],
					"color" : [ 0.709562, 0.005658, 0.121731, 1.0 ],
					"id" : "obj-116",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 497.5, 337.5, 100.0, 22.0 ],
					"text" : "minimum~"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.313974, 0.0, 0.048004, 1.0 ],
					"color" : [ 0.709562, 0.005658, 0.121731, 1.0 ],
					"id" : "obj-115",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 310.5, 337.5, 100.0, 22.0 ],
					"text" : "minimum~"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.52549, 0.062745, 0.003922, 1.0 ],
					"format" : 6,
					"id" : "obj-102",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 837.5, 155.5, 50.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-103",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 867.5, 128.5, 103.0, 20.0 ],
					"text" : "Tropical beatings"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.52549, 0.062745, 0.003922, 1.0 ],
					"format" : 6,
					"id" : "obj-104",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 814.0, 128.5, 50.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.52549, 0.062745, 0.003922, 1.0 ],
					"color" : [ 0.730568, 0.031973, 0.071635, 1.0 ],
					"id" : "obj-105",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "float" ],
					"patching_rect" : [ 803.5, 155.5, 29.5, 22.0 ],
					"text" : "+ 0."
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-106",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 936.5, 219.5, 43.0, 20.0 ],
					"text" : "Ø"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.65908, 0.0065, 0.107064, 1.0 ],
					"format" : 6,
					"id" : "obj-107",
					"maxclass" : "flonum",
					"maximum" : 1.0,
					"minimum" : 0.0,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 884.5, 217.5, 50.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-108",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 905.5, 248.5, 43.0, 20.0 ],
					"text" : "VCO2"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-109",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 905.5, 307.0, 82.0, 20.0 ],
					"text" : "Tropical VCA"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.52549, 0.062745, 0.003922, 1.0 ],
					"color" : [ 0.730568, 0.031973, 0.071635, 1.0 ],
					"id" : "obj-110",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "float" ],
					"patching_rect" : [ 803.5, 189.5, 29.5, 22.0 ],
					"text" : "* 5."
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.65908, 0.0065, 0.107064, 1.0 ],
					"format" : 6,
					"id" : "obj-111",
					"maxclass" : "flonum",
					"maximum" : 1.0,
					"minimum" : -1.0,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 884.5, 277.0, 50.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.313974, 0.0, 0.048004, 1.0 ],
					"color" : [ 0.709562, 0.005658, 0.121731, 1.0 ],
					"id" : "obj-112",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 803.5, 305.0, 100.0, 22.0 ],
					"text" : "+~"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.52549, 0.062745, 0.003922, 1.0 ],
					"format" : 6,
					"id" : "obj-113",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 803.5, 217.5, 50.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.313974, 0.0, 0.048004, 1.0 ],
					"color" : [ 0.709562, 0.005658, 0.121731, 1.0 ],
					"id" : "obj-114",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 803.5, 246.5, 100.0, 22.0 ],
					"text" : "cycle~"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.52549, 0.062745, 0.003922, 1.0 ],
					"format" : 6,
					"id" : "obj-89",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 641.5, 153.5, 50.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-90",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 671.5, 126.5, 103.0, 20.0 ],
					"text" : "Tropical beatings"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.52549, 0.062745, 0.003922, 1.0 ],
					"format" : 6,
					"id" : "obj-91",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 618.0, 126.5, 50.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.52549, 0.062745, 0.003922, 1.0 ],
					"color" : [ 0.730568, 0.031973, 0.071635, 1.0 ],
					"id" : "obj-92",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "float" ],
					"patching_rect" : [ 607.5, 153.5, 29.5, 22.0 ],
					"text" : "+ 0."
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-93",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 740.5, 217.5, 43.0, 20.0 ],
					"text" : "Ø"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.65908, 0.0065, 0.107064, 1.0 ],
					"format" : 6,
					"id" : "obj-94",
					"maxclass" : "flonum",
					"maximum" : 1.0,
					"minimum" : 0.0,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 688.5, 215.5, 50.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-95",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 709.5, 246.5, 43.0, 20.0 ],
					"text" : "VCO2"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-96",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 709.5, 305.0, 82.0, 20.0 ],
					"text" : "Tropical VCA"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.52549, 0.062745, 0.003922, 1.0 ],
					"color" : [ 0.730568, 0.031973, 0.071635, 1.0 ],
					"id" : "obj-97",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "float" ],
					"patching_rect" : [ 607.5, 187.5, 29.5, 22.0 ],
					"text" : "* 4."
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.65908, 0.0065, 0.107064, 1.0 ],
					"format" : 6,
					"id" : "obj-98",
					"maxclass" : "flonum",
					"maximum" : 1.0,
					"minimum" : -1.0,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 688.5, 275.0, 50.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.313974, 0.0, 0.048004, 1.0 ],
					"color" : [ 0.709562, 0.005658, 0.121731, 1.0 ],
					"id" : "obj-99",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 607.5, 303.0, 100.0, 22.0 ],
					"text" : "+~"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.52549, 0.062745, 0.003922, 1.0 ],
					"format" : 6,
					"id" : "obj-100",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 607.5, 215.5, 50.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.313974, 0.0, 0.048004, 1.0 ],
					"color" : [ 0.709562, 0.005658, 0.121731, 1.0 ],
					"id" : "obj-101",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 607.5, 244.5, 100.0, 22.0 ],
					"text" : "cycle~"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.52549, 0.062745, 0.003922, 1.0 ],
					"format" : 6,
					"id" : "obj-76",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 450.5, 151.5, 50.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-77",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 480.5, 124.5, 103.0, 20.0 ],
					"text" : "Tropical beatings"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.52549, 0.062745, 0.003922, 1.0 ],
					"format" : 6,
					"id" : "obj-78",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 427.0, 124.5, 50.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.52549, 0.062745, 0.003922, 1.0 ],
					"color" : [ 0.730568, 0.031973, 0.071635, 1.0 ],
					"id" : "obj-79",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "float" ],
					"patching_rect" : [ 416.5, 151.5, 29.5, 22.0 ],
					"text" : "+ 0."
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-80",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 549.5, 215.5, 43.0, 20.0 ],
					"text" : "Ø"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.65908, 0.0065, 0.107064, 1.0 ],
					"format" : 6,
					"id" : "obj-81",
					"maxclass" : "flonum",
					"maximum" : 1.0,
					"minimum" : 0.0,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 497.5, 213.5, 50.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-82",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 518.5, 244.5, 43.0, 20.0 ],
					"text" : "VCO2"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-83",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 518.5, 303.0, 82.0, 20.0 ],
					"text" : "Tropical VCA"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.52549, 0.062745, 0.003922, 1.0 ],
					"color" : [ 0.730568, 0.031973, 0.071635, 1.0 ],
					"id" : "obj-84",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "float" ],
					"patching_rect" : [ 416.5, 185.5, 29.5, 22.0 ],
					"text" : "* 3."
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.65908, 0.0065, 0.107064, 1.0 ],
					"format" : 6,
					"id" : "obj-85",
					"maxclass" : "flonum",
					"maximum" : 1.0,
					"minimum" : -1.0,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 497.5, 273.0, 50.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.313974, 0.0, 0.048004, 1.0 ],
					"color" : [ 0.709562, 0.005658, 0.121731, 1.0 ],
					"id" : "obj-86",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 416.5, 301.0, 100.0, 22.0 ],
					"text" : "+~"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.52549, 0.062745, 0.003922, 1.0 ],
					"format" : 6,
					"id" : "obj-87",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 416.5, 213.5, 50.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.313974, 0.0, 0.048004, 1.0 ],
					"color" : [ 0.709562, 0.005658, 0.121731, 1.0 ],
					"id" : "obj-88",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 416.5, 242.5, 100.0, 22.0 ],
					"text" : "cycle~"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.52549, 0.062745, 0.003922, 1.0 ],
					"format" : 6,
					"id" : "obj-75",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 261.5, 149.5, 50.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-74",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 290.5, 122.5, 103.0, 20.0 ],
					"text" : "Tropical beatings"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.52549, 0.062745, 0.003922, 1.0 ],
					"format" : 6,
					"id" : "obj-72",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 237.0, 122.5, 50.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.52549, 0.062745, 0.003922, 1.0 ],
					"color" : [ 0.730568, 0.031973, 0.071635, 1.0 ],
					"id" : "obj-71",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "float" ],
					"patching_rect" : [ 226.5, 149.5, 29.5, 22.0 ],
					"text" : "+ 0."
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-59",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 611.5, 70.0, 134.0, 20.0 ],
					"text" : "Calculate 4th harmonic"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-37",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 416.5, 68.0, 181.0, 20.0 ],
					"text" : "Calculate 3d harmonic"
				}

			}
, 			{
				"box" : 				{
					"angle" : 270.0,
					"bgcolor" : [ 0.397309, 0.023578, 0.040094, 1.0 ],
					"id" : "obj-45",
					"maxclass" : "panel",
					"mode" : 0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 11.0, 642.0, 1176.0, 54.5 ],
					"proportion" : 0.39
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-38",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 802.5, 25.0, 311.0, 20.0 ],
					"text" : "Tropical Additive Synthesis @2018 Bocci-Sancristoforo",
					"textcolor" : [ 1.0, 1.0, 1.0, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-35",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 153.5, 207.5, 43.0, 20.0 ],
					"text" : "Ø"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-18",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 359.5, 213.5, 43.0, 20.0 ],
					"text" : "Ø"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.65908, 0.0065, 0.107064, 1.0 ],
					"format" : 6,
					"id" : "obj-2",
					"maxclass" : "flonum",
					"maximum" : 1.0,
					"minimum" : 0.0,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 307.5, 211.5, 50.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.65908, 0.0065, 0.107064, 1.0 ],
					"format" : 6,
					"id" : "obj-5",
					"maxclass" : "flonum",
					"maximum" : 1.0,
					"minimum" : 0.0,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 101.5, 207.5, 50.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Times Italic",
					"fontsize" : 30.0,
					"id" : "obj-25",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 21.0, 10.25, 140.0, 36.0 ],
					"text" : "trop(x[n])",
					"textcolor" : [ 1.0, 1.0, 1.0, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.313726, 0.0, 0.047059, 0.0 ],
					"id" : "obj-70",
					"maxclass" : "ezdac~",
					"numinlets" : 2,
					"numoutlets" : 0,
					"patching_rect" : [ 1115.5, 15.5, 34.0, 34.0 ]
				}

			}
, 			{
				"box" : 				{
					"angle" : 270.0,
					"bgcolor" : [ 0.392156862745098, 0.019607843137255, 0.035294117647059, 1.0 ],
					"id" : "obj-20",
					"maxclass" : "panel",
					"mode" : 0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 392.0, -6.5, 795.0, 29.5 ],
					"proportion" : 0.39
				}

			}
, 			{
				"box" : 				{
					"fontface" : 3,
					"fontname" : "Times Italic",
					"fontsize" : 13.0,
					"id" : "obj-17",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 438.0, 25.0, 120.0, 19.0 ]
				}

			}
, 			{
				"box" : 				{
					"hidden" : 1,
					"id" : "obj-73",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 990.75, 445.0, 100.0, 22.0 ],
					"text" : "loadmess 100"
				}

			}
, 			{
				"box" : 				{
					"hidden" : 1,
					"id" : "obj-64",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 652.75, 384.0, 100.0, 22.0 ],
					"text" : "loadmess 0.5"
				}

			}
, 			{
				"box" : 				{
					"hidden" : 1,
					"id" : "obj-34",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 0,
					"patching_rect" : [ 683.25, 616.0, 39.0, 22.0 ],
					"text" : "dac~"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.412528, 0.003289, 0.070772, 1.0 ],
					"id" : "obj-33",
					"maxclass" : "meter~",
					"numinlets" : 1,
					"numleds" : 20,
					"numoutlets" : 1,
					"outlettype" : [ "float" ],
					"patching_rect" : [ 701.25, 469.0, 24.0, 162.0 ]
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.412528, 0.003289, 0.070772, 1.0 ],
					"id" : "obj-32",
					"maxclass" : "gain~",
					"multichannelvariant" : 0,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "signal", "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 682.25, 469.0, 18.0, 162.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-30",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 328.5, 242.5, 43.0, 20.0 ],
					"text" : "VCO2"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-29",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 122.5, 236.5, 43.0, 20.0 ],
					"text" : "VCO1"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-28",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 237.0, 68.0, 144.0, 20.0 ],
					"text" : "Calculate 2nd harmonic"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-27",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 75.0, 68.0, 138.0, 20.0 ],
					"text" : "Fundamental frequency"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-24",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 784.25, 415.0, 238.0, 20.0 ],
					"text" : "Another Tropical VCA to correct DC offset"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-23",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 129.0, 337.5, 92.0, 20.0 ],
					"text" : "Tropical MIXER"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-22",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 122.5, 297.0, 82.0, 20.0 ],
					"text" : "Tropical VCA"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-21",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 328.5, 301.0, 82.0, 20.0 ],
					"text" : "Tropical VCA"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.313974, 0.0, 0.048004, 1.0 ],
					"id" : "obj-19",
					"maxclass" : "spectroscope~",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 901.75, 469.0, 189.0, 162.0 ]
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.65908, 0.0065, 0.107064, 1.0 ],
					"format" : 6,
					"id" : "obj-15",
					"maxclass" : "flonum",
					"maximum" : 2.0,
					"minimum" : -2.0,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 763.25, 384.0, 50.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.239307, 0.0, 0.047463, 1.0 ],
					"color" : [ 0.709562, 0.005658, 0.121731, 1.0 ],
					"id" : "obj-16",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 682.25, 414.0, 100.0, 22.0 ],
					"text" : "+~"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.52549, 0.062745, 0.003922, 1.0 ],
					"color" : [ 0.730568, 0.031973, 0.071635, 1.0 ],
					"id" : "obj-13",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "float" ],
					"patching_rect" : [ 226.5, 183.5, 54.0, 22.0 ],
					"text" : "* 2."
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.313974, 0.0, 0.048004, 1.0 ],
					"bufsize" : 101,
					"calccount" : 6,
					"id" : "obj-12",
					"maxclass" : "scope~",
					"numinlets" : 2,
					"numoutlets" : 0,
					"patching_rect" : [ 728.75, 469.0, 171.0, 162.0 ]
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.65908, 0.0065, 0.107064, 1.0 ],
					"format" : 6,
					"id" : "obj-8",
					"maxclass" : "flonum",
					"maximum" : 1.0,
					"minimum" : -1.0,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 307.5, 271.0, 50.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.313974, 0.0, 0.048004, 1.0 ],
					"color" : [ 0.709562, 0.005658, 0.121731, 1.0 ],
					"id" : "obj-9",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 226.5, 299.0, 100.0, 22.0 ],
					"text" : "+~"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.52549, 0.062745, 0.003922, 1.0 ],
					"format" : 6,
					"id" : "obj-10",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 226.5, 211.5, 50.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.313974, 0.0, 0.048004, 1.0 ],
					"color" : [ 0.709562, 0.005658, 0.121731, 1.0 ],
					"id" : "obj-11",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 226.5, 240.5, 100.0, 22.0 ],
					"text" : "cycle~"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.313974, 0.0, 0.048004, 1.0 ],
					"color" : [ 0.709562, 0.005658, 0.121731, 1.0 ],
					"id" : "obj-7",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 20.5, 337.5, 100.0, 22.0 ],
					"text" : "minimum~"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.65908, 0.0065, 0.107064, 1.0 ],
					"format" : 6,
					"id" : "obj-6",
					"maxclass" : "flonum",
					"maximum" : 1.0,
					"minimum" : -1.0,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 101.5, 267.0, 50.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.313974, 0.0, 0.048004, 1.0 ],
					"color" : [ 0.709562, 0.005658, 0.121731, 1.0 ],
					"id" : "obj-4",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 20.5, 295.0, 100.0, 22.0 ],
					"text" : "+~"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.52549, 0.062745, 0.003922, 1.0 ],
					"format" : 6,
					"id" : "obj-3",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 21.0, 67.0, 50.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.313974, 0.0, 0.048004, 1.0 ],
					"color" : [ 0.709562, 0.005658, 0.121731, 1.0 ],
					"id" : "obj-1",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 21.0, 236.5, 100.0, 22.0 ],
					"text" : "cycle~"
				}

			}
, 			{
				"box" : 				{
					"angle" : 270.0,
					"bgcolor" : [ 0.397309, 0.023578, 0.040094, 1.0 ],
					"id" : "obj-44",
					"maxclass" : "panel",
					"mode" : 0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 11.0, -1.5, 1176.0, 59.5 ],
					"proportion" : 0.39
				}

			}
, 			{
				"box" : 				{
					"angle" : 270.0,
					"bgcolor" : [ 0.397309, 0.023578, 0.040094, 0.31 ],
					"id" : "obj-26",
					"maxclass" : "panel",
					"mode" : 0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 672.75, 375.5, 422.0, 83.0 ],
					"proportion" : 0.39
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"destination" : [ "obj-4", 0 ],
					"source" : [ "obj-1", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-11", 0 ],
					"source" : [ "obj-10", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-101", 0 ],
					"source" : [ "obj-100", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-99", 0 ],
					"source" : [ "obj-101", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-110", 1 ],
					"source" : [ "obj-102", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-105", 1 ],
					"order" : 0,
					"source" : [ "obj-104", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-131", 0 ],
					"hidden" : 1,
					"order" : 1,
					"source" : [ "obj-104", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-110", 0 ],
					"source" : [ "obj-105", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-114", 1 ],
					"source" : [ "obj-107", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-9", 0 ],
					"source" : [ "obj-11", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-113", 0 ],
					"source" : [ "obj-110", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-112", 1 ],
					"source" : [ "obj-111", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-117", 1 ],
					"source" : [ "obj-112", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-114", 0 ],
					"source" : [ "obj-113", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-112", 0 ],
					"source" : [ "obj-114", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-116", 0 ],
					"source" : [ "obj-115", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-117", 0 ],
					"source" : [ "obj-116", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-16", 0 ],
					"source" : [ "obj-117", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-79", 0 ],
					"hidden" : 1,
					"source" : [ "obj-122", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-71", 0 ],
					"hidden" : 1,
					"source" : [ "obj-124", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-10", 0 ],
					"source" : [ "obj-13", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-92", 0 ],
					"hidden" : 1,
					"source" : [ "obj-130", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-105", 0 ],
					"hidden" : 1,
					"source" : [ "obj-131", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-16", 1 ],
					"source" : [ "obj-15", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-12", 0 ],
					"hidden" : 1,
					"midpoints" : [ 691.75, 445.5, 738.25, 445.5 ],
					"order" : 1,
					"source" : [ "obj-16", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-19", 0 ],
					"hidden" : 1,
					"midpoints" : [ 691.75, 445.5, 911.25, 445.5 ],
					"order" : 0,
					"source" : [ "obj-16", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-32", 0 ],
					"midpoints" : [ 691.75, 448.0, 691.75, 448.0 ],
					"order" : 2,
					"source" : [ "obj-16", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-48", 1 ],
					"order" : 3,
					"source" : [ "obj-16", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-48", 0 ],
					"order" : 4,
					"source" : [ "obj-16", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-11", 1 ],
					"source" : [ "obj-2", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"order" : 4,
					"source" : [ "obj-3", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-105", 0 ],
					"midpoints" : [ 30.5, 104.75, 813.0, 104.75 ],
					"order" : 0,
					"source" : [ "obj-3", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-71", 0 ],
					"midpoints" : [ 30.5, 101.75, 236.0, 101.75 ],
					"order" : 3,
					"source" : [ "obj-3", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-79", 0 ],
					"midpoints" : [ 30.5, 104.75, 426.0, 104.75 ],
					"order" : 2,
					"source" : [ "obj-3", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-92", 0 ],
					"midpoints" : [ 30.5, 102.75, 617.0, 102.75 ],
					"order" : 1,
					"source" : [ "obj-3", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-33", 0 ],
					"hidden" : 1,
					"order" : 1,
					"source" : [ "obj-32", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-34", 1 ],
					"hidden" : 1,
					"midpoints" : [ 689.25, 616.25, 712.75, 616.25 ],
					"order" : 0,
					"source" : [ "obj-32", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-34", 0 ],
					"hidden" : 1,
					"midpoints" : [ 689.25, 616.25, 692.75, 616.25 ],
					"order" : 2,
					"source" : [ "obj-32", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-47", 1 ],
					"source" : [ "obj-39", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 0 ],
					"source" : [ "obj-4", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-47", 0 ],
					"source" : [ "obj-46", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-43", 0 ],
					"source" : [ "obj-47", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-43", 1 ],
					"source" : [ "obj-49", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 1 ],
					"midpoints" : [ 111.0, 235.0 ],
					"source" : [ "obj-5", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-4", 1 ],
					"source" : [ "obj-6", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-15", 0 ],
					"hidden" : 1,
					"source" : [ "obj-64", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-115", 0 ],
					"source" : [ "obj-7", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-13", 0 ],
					"source" : [ "obj-71", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-124", 0 ],
					"hidden" : 1,
					"order" : 1,
					"source" : [ "obj-72", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-71", 1 ],
					"order" : 0,
					"source" : [ "obj-72", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-32", 0 ],
					"hidden" : 1,
					"midpoints" : [ 1000.25, 478.5, 849.75, 478.5, 849.75, 458.0, 691.75, 458.0 ],
					"source" : [ "obj-73", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-13", 1 ],
					"source" : [ "obj-75", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-84", 1 ],
					"source" : [ "obj-76", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-122", 0 ],
					"hidden" : 1,
					"order" : 1,
					"source" : [ "obj-78", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-79", 1 ],
					"order" : 0,
					"source" : [ "obj-78", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-84", 0 ],
					"source" : [ "obj-79", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-9", 1 ],
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-88", 1 ],
					"source" : [ "obj-81", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-87", 0 ],
					"source" : [ "obj-84", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-86", 1 ],
					"source" : [ "obj-85", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-115", 1 ],
					"source" : [ "obj-86", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-88", 0 ],
					"source" : [ "obj-87", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-86", 0 ],
					"source" : [ "obj-88", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-97", 1 ],
					"source" : [ "obj-89", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 1 ],
					"midpoints" : [ 236.0, 324.75, 111.0, 324.75 ],
					"source" : [ "obj-9", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-130", 0 ],
					"hidden" : 1,
					"order" : 1,
					"source" : [ "obj-91", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-92", 1 ],
					"order" : 0,
					"source" : [ "obj-91", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-97", 0 ],
					"source" : [ "obj-92", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-101", 1 ],
					"source" : [ "obj-94", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-100", 0 ],
					"source" : [ "obj-97", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-99", 1 ],
					"source" : [ "obj-98", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-116", 1 ],
					"source" : [ "obj-99", 0 ]
				}

			}
 ],
		"dependency_cache" : [  ],
		"autosave" : 0
	}

}
