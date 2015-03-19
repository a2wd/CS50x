<div id="quote">
	<span id="ticker">(<?= $values["symbol"] ?>)</span> <span id="name"><?= $values["name"] ?></span>
	is currently valued at <span id="price"><?= $values["price"] ?></span>
</div>
<div>
	You can
	<form action="buy.php" method="post">
		<input type="submit" name="buy" value="Buy" /> now or...
		<input type="hidden" name="stock" value="<?= $values["symbol"] ?>" />
	</form>
</div>
<div>
    get another <a href="quote.php">quote</a>, or
</div>
<div>
    return to your <a href="index.php">homepage</a>
</div>
