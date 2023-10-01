#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>

// Timer.3 Binding arguments to a handler
// Notes:
// 	Boost Bind is not exactly like the std::bind: https://www.boost.org/libs/bind/bind.html

void print(const boost::system::error_code& /*e*/, boost::asio::steady_timer* t, int *count)
{
	if (*count < 5) {
		std::cout << *count << std::endl;
		++(*count);
		t->expires_at(t->expiry() + boost::asio::chrono::seconds(1));
		// need to create a new function object for this instance of async_wait with the current
		// parameters but a smaller count value, a valid question here would be: what happens
		// with the previously registered function object?  (it should get destroyed as it's
		// replaced)
		t->async_wait(boost::bind(print, boost::asio::placeholders::error, t, count));
	}
}

int main(int,char**) {
	boost::asio::io_context io;
	int count = 0;
	boost::asio::steady_timer t(io, boost::asio::chrono::seconds(1));
	t.async_wait(boost::bind(print, boost::asio::placeholders::error, &t, &count));
	io.run();
	std::cout << "Final count is " << count << std::endl;
	return 0;
}
