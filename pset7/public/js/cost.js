$(document).ready(function(){

	//Initialise cost div
	var placeholder = "===";
	var cost = parseFloat($("#price").text());
	$("#cost").html(placeholder);
	
	$("#quantity").change(function(){
		var num = $("#quantity").val();
		if($.isNumeric(num))
		{
			var price = cost * num;
			var info = "To buy " + num + " shares at $" + cost + " will cost $" + price.toFixed(2);
			$("#cost").html(info);
		}
		else
		{
			//Not a number, replace text with placeholder
			$("#cost").html(placeholder);
		}
	});
});
