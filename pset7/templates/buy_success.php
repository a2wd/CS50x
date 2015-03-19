<div>
	<h2>Congratulations on your purchase</h2>
	<p>
		You bought <?= $quantity ?> shares of <?= $quote["name"] ?>
		at $<?= $quote["price"] ?> for a sum of $<?= $cost ?>.
	</p>
	<p>
		Now you can go <a href="index.php">home</a> or get another <a href="quote.php">quote!</a>
	</p>
	<div id="cash">
		You currently have <code>$<?= $cash ?></code> to burn!
	</div>	
	<br />
	<p>
		<small>I only ask that you judge me on my losers because I have so few</small>
	</p>
</div>
