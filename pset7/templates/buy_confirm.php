<div>
	<h2>Confirm your purchase!</h2>
	<p>This quote will be valid for 5 minutes only</p>
	<p>
		You want to buy: <?= $quote["name"] ?> (<?= $quote["symbol"] ?>),
		this is currently valued at <span id="price"><?= $quote["price"] ?></span>
	</p>
	<form action="buy.php" method="post">
		Yes! Give me the once in a lifetime opportunity to buy: 
		<input id="quantity" type="number" name="quantity" /> shares now.
		<br />
		<div id="cost"></div>
		<input type="submit" name="confirm" value="Buy!" />
		<input type="hidden" name="stock" value="<?= $quote["symbol"] ?>" />
	</form>
</div>
<div id="cash">
	You currently have <code>$<?= $cash ?></code> to burn!
</div>
<div>
	...Or else go <a href="index.php">home</a>
</div>
<script src="js/cost.js" type="text/javascript"></script>
