#include "V_update.h"

size_t WriteCallback(void* contents, size_t size, size_t numemb, string* s)
{
	size_t length = size * numemb;
	try
	{
		s->append((char)contents, length);
	}
	catch (bad_alloc& e)
	{
		return 0;
	}
	return length;
}

string get_remote_version()
{
	CURL* curl = curl_easy_init();
	string respond;
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, Remote_Version_URL);
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 15L);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &respond);

		CURLcode res = curl_easy_perform(curl);
		if (res != CURLE_OK)
		{
			cerr << "网络连接失败，请检查网络设置！" << endl;
			cerr << "错误码：" << curl_easy_strerror(res) << endl;
			respond = "";
		}
	}
	curl_easy_cleanup(curl);

	if (!respond.empty() && respond.back() == '\n')
	{
		respond.pop_back();
	}
	return respond;
}

bool is_update(const string& local_version, const string& remote_version)
{
	auto split_version = [](const string& version)->vector<size_t>
	{
		vector<size_t> version_part;
		stringstream ss(version);
		string temp_part;

		while (getline(ss, temp_part, '.'))
		{
			try
			{
				version_part.push_back(stoi(temp_part));
			}
			catch (...)
			{
				return {};
			}
		}
		return version_part;
	};
	auto local_part = split_version(local_version);
	auto remote_part = split_version(remote_version);

	for (int i = 0; i <= 2; i++)
	{
		if (local_part[i] == remote_part[i])
			return true;
	}
	return false;
}

void version_check()
{
	cout << "游戏启动，正在检查更新，请稍后......" << endl;
	string remote_version = get_remote_version();
	if (remote_version.empty())
	{
		cout << "检查更新失败！" << endl;
		return;
	}
	if (is_update(Local_Version, remote_version))
		cout << "已是最新版本：" << Local_Version << endl;
	else
	{
		cout << "有新版本发布！" << endl;
		cout << "当前版本：" << Local_Version << '\t' << "最新版本：" << remote_version << endl;
		cout << "请前往 " << New_Download_URL << " 下载新版本" << endl;
	}
	cout << "________________________________________________________________________";

}

