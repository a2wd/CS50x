<div>
	Do you want to liquidate your holdings in <?= $quote["name"] ?>?
</div>
<div id="details">
	<span><?= $quote["stock"] ?></span>
	<span><?= $quote["name"] ?></span>
	<span><?= $quote["price"] ?></span>
	<span><?= $quote["quantity"] ?></span>
	<span><?= $quote["value"] ?></span>
</div>
<div>
	This quote is valid for 5 minutes, sell now and <?= $quote["value"] ?> will be credited to your account
</div>
<form id="sell" action="sell.php" method="post"><button name="confirm" value="<?= $quote["stock"] ?>">Sell</button></form><a href="javascript:history.go(-1);">Go back</a>
