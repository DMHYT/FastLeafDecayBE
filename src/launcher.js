const json = FileTools.ReadJSON(__packdir__ + "manifest.json");
const version = parseInt(json.gameVersion.split(".")[1])
if(version >= 16) {
	ConfigureMultiplayer({
		name: "Fast Leaf Decay",
		version: "1.0",
		isClientOnly: false
	});
	Launch();
} else throw new Error("Fast Leaf Decay mod only works on Minecraft BE 1.16.201 and above (in future). You are currently playing on 1." + version + ".x version! If you are using InnerCore Legacy pack, consider moving to the main one, if you want to use Fast Leaf Decay mod!");